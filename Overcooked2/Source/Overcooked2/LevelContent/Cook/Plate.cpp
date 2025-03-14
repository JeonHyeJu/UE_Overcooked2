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

	FRotator Rotator = FRotator(0.0f, 0.0f, 90.0f);
	StaticMeshComponent->SetRelativeRotation(FRotator(Rotator)); // y z x

	FVector Scale = FVector(2.0f, 2.0f, 2.0f);
	StaticMeshComponent->SetRelativeScale3D(Scale);
}

void APlate::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlate, Ingredients);
	DOREPLIFETIME(APlate, IngredientMesh);
	DOREPLIFETIME(APlate, PlateState);
	//DOREPLIFETIME(APlate, PrveState);
}

// Called when the game starts or when spawned
void APlate::BeginPlay()
{
	ACooking::BeginPlay();
	
	SetActorLocation(FVector(0.0f, -200.0f, 10.0f));
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
	}
}

void APlate::SetPlateState_Implementation(EPlateState State)
{
	PlateState = State;
}

bool APlate::Add(AIngredient* Ingredient)
{
	if (ECookingType::ECT_INGREDIENT != Ingredient->GetCookingType())
	{
		return false;
	}
	if (EPlateState::COMPLETED == PlateState || EPlateState::DIRTY == PlateState)
	{	// �̹� �ϼ��� �丮�� ��ô ���� ���ô� ��Ḧ �ø� �� ����.
		return false;
	}
	if (EIngredientState::EIS_NONE == Ingredient->GetCurIngredientState())
	{	// �������� ���� ���� ���ÿ� �ø� �� ����.
		return false;
	}
	if (nullptr == StaticMeshComponent)
	{
		return false;
	}

	// 1. ������ ��Ḧ �߰��Ѵ�.
	Ingredients.Add(Ingredient);

	// 2. RecipeDataTable�� ���Ͽ� ������ ���̺� �ش� ��������� �����ϴ��� Ȯ��
	TArray<FPlateInitData> InitData = UOC2GlobalData::GetPlateMesh(GetWorld(), Ingredients);

	// 3-1. �����͸� ȹ���ϴµ� �����ߴٸ�
	if (true == InitData.IsEmpty()) 
	{
		Ingredients.Pop(); // ��� �ڷᱸ������ �����ϰ� ���� ��ȯ
		return false;
	}
	else // 3-2. �����͸� ȹ���ϴµ� �����ߴٸ� 
	{
		IngredientMesh->SetStaticMesh(InitData[0].StaticMesh); // �޽� ����
		if (nullptr != IngredientMesh)
		{
			// 3-3. ���� ��� ����
			SetSimulatePhysics(false); // ������Ʈ�� �浹�� ���ư��� �����̴� ���� �����ϱ� ���� ������ ��� ����.
			IngredientMesh->AttachToComponent(StaticMeshComponent, FAttachmentTransformRules::KeepRelativeTransform);

			// 3-4. Offset
			IngredientMesh->AddLocalOffset(InitData[0].OffsetLocation);
			IngredientMesh->SetRelativeRotation(InitData[0].OffsetRotation);
			IngredientMesh->SetRelativeScale3D(InitData[0].OffsetScale);

			// 3-5. ���� �ٽ� �Ѱ�
			SetSimulatePhysics(true);
			return true;
		}
	}
	return false;
}
