// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelContent/Cook/Plate.h"
#include <LevelContent/Cook/Ingredient.h>
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include <Global/Data/OC2GlobalData.h>

// Sets default values
APlate::APlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	CookingType = ECookingType::ECT_PLATE;

	IngredientMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("IngredientMesh"));
	IngredientMesh->SetIsReplicated(true); // ������Ʈ ��Ʈ��ũ ����ȭ

	FVector Scale = FVector(2.0f, 2.0f, 2.0f);
	StaticMeshComponent->SetRelativeScale3D(Scale);

	// Debug
	SetActorLocation(FVector(0.0f, -200.0f, 10.0f));
}

void APlate::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlate, Ingredients);
	DOREPLIFETIME(APlate, IngredientMesh);
	DOREPLIFETIME(APlate, PlateState);
}

// Called when the game starts or when spawned
void APlate::BeginPlay()
{
	ACooking::BeginPlay();
	
}

// Called every frame
void APlate::Tick(float DeltaTime)
{
	ACooking::Tick(DeltaTime);

}

bool APlate::IsDirtyPlate()
{
	if (nullptr == StaticMeshComponent)
	{
		return false;
	}

	return PlateState == EPlateState::DIRTY;
}

void APlate::WashPlate_Implementation()
{
	if (true == IsDirtyPlate())
	{
		PlateState = EPlateState::EMPTY;
		SetMesh();
	}
}

void APlate::SetPlateState_Implementation(EPlateState State)
{
	PlateState = State;
	SetMesh();
}

void APlate::SetMesh()
{
	UTexture* Texture = nullptr;
	if (EPlateState::DIRTY == PlateState)
	{
		Texture = DirtyTexture;
	}
	else
	{
		Texture = CleanTexture;
	}
	SetMaterialTexture(Texture);
}

void APlate::SetMaterialTexture(UTexture* Texture)
{
	// 1. ����ƽ �޽��� ��Ƽ������ �ٲܰǵ�

	// 2. �̹� �������� ������ ��Ƽ���� �ν��Ͻ� ���̳����� �����ϸ� 
	UMaterialInstanceDynamic* MaterialInstanceDynamic = Cast<UMaterialInstanceDynamic>(StaticMeshComponent->GetMaterial(0));
	if (nullptr != MaterialInstanceDynamic)
	{
		// 3. ���� ��Ƽ���� �ν��Ͻ� ���̳����� �״�� ����ϰ�
		MaterialInstanceDynamic->SetTextureParameterValue(FName(TEXT("DiffuseAdd")), Texture);
		StaticMeshComponent->SetMaterial(0, MaterialInstanceDynamic);
		return;
	}

	// 4. ������ ������� ��Ƽ���� �ν��Ͻ� ���̳����� ���ٸ� == SetMaterial�� ó���̶��
	UMaterialInterface* Material = StaticMeshComponent->GetMaterial(0);
	if (nullptr != Material)
	{
		// 5. ���� ������ ��Ƽ������ �Ⱦ��� ��Ƽ���� �ν��Ͻ� ���̳����� ���� �� ���̴�.
		UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
		if (nullptr != DynamicMaterial)
		{
			// 6. �ٲ� �ؽ�ó�� �����Ϳ��� ��������ٸ� �װɷ� �ٲ��.
			if (nullptr != Texture)
			{
				DynamicMaterial->SetTextureParameterValue(FName(TEXT("DiffuseAdd")), Texture);
				StaticMeshComponent->SetMaterial(0, DynamicMaterial);
			}
		}
	}
}

void APlate::Add_Implementation(AIngredient* Ingredient)
{
	bIsCombinationSuccessful = false;
	if (ECookingType::ECT_INGREDIENT != Ingredient->GetCookingType())
	{
		return;
	}
	if (EPlateState::COMPLETED == PlateState || EPlateState::DIRTY == PlateState)
	{	// �̹� �ϼ��� �丮�� ��ô ���� ���ô� ��Ḧ �ø� �� ����.
		return;
	}
	if (EIngredientState::EIS_NONE == Ingredient->GetCurIngredientState())
	{	// �������� ���� ���� ���ÿ� �ø� �� ����.
		return;
	}
	if (nullptr == StaticMeshComponent)
	{
		return;
	}

	// 1. ������ ��Ḧ �߰��Ѵ�.
	Ingredients.Add(Ingredient);

	// 2. RecipeDataTable�� ���Ͽ� ������ ���̺� �ش� ��������� �����ϴ��� Ȯ��
	TArray<FPlateInitData> InitData = UOC2GlobalData::GetPlateMesh(GetWorld(), Ingredients);

	// 3-1. �����͸� ȹ���ϴµ� �����ߴٸ�
	if (true == InitData.IsEmpty()) 
	{
		Ingredients.Pop(); // ��� �ڷᱸ������ �����ϰ� ���� ��ȯ
		return;
	}
	else // 3-2. �����͸� ȹ���ϴµ� �����ߴٸ� 
	{
		IngredientMesh->SetStaticMesh(InitData[0].StaticMesh); // �޽� ����
		if (nullptr != IngredientMesh)
		{
			// 3-3. ���� ��� ����
			SetSimulatePhysics(false); // ������Ʈ�� �浹�� ���ư��� �����̴� ���� �����ϱ� ���� ������ ��� ����.

			// 3-4. IngredientMesh�� �浹ü�� ������ ����.
			IngredientMesh->AttachToComponent(StaticMeshComponent, FAttachmentTransformRules::KeepRelativeTransform);
			IngredientMesh->SetCollisionProfileName(TEXT("NoCollision"));
			IngredientMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			IngredientMesh->SetSimulatePhysics(false);

			// 3-5. Offset
			IngredientMesh->SetRelativeLocation(InitData[0].OffsetLocation); // ���� �ʿ� Add -> Set
			IngredientMesh->SetRelativeRotation(InitData[0].OffsetRotation);
			IngredientMesh->SetRelativeScale3D(InitData[0].OffsetScale);

			// 3-6. ���� �ٽ� �Ѱ�
			SetSimulatePhysics(true);
			bIsCombinationSuccessful = true;
			return;
		}
	}
	return;
}
