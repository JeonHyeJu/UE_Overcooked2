// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelContent/Cook/Plate.h"
#include <LevelContent/Cook/Ingredient.h>
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include <Global/Data/OC2GlobalData.h>
#include "Components/BillboardComponent.h"  

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


	int MaxTexture = 3;
	for (int i = 0; i < MaxTexture; i++)
	{
		FString ComponentName = FString::Printf(TEXT("TextureBillboard_%d"), i);
		UBillboardComponent* BillboardComponent = CreateDefaultSubobject<UBillboardComponent>(*ComponentName);
		BillboardComponent->SetupAttachment(RootComponent);
		TextureBillboards.Add(BillboardComponent);
	}

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

bool APlate::CanPlaceOnPlate(AIngredient* Ingredient)
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
	return true;
}

void APlate::Add_Implementation(AIngredient* Ingredient)
{
	bIsCombinationSuccessful = false;

	if (false == CanPlaceOnPlate(Ingredient))
	{
		return;
	}

	// 1. ������ ��Ḧ �߰��Ѵ�.
	FRecipe Recipe;
	Recipe.IngredientType = Ingredient->GetIngredientType();
	Recipe.IngredientState = Ingredient->GetCurIngredientState();
	Ingredients.Add(Recipe);

	// 2. RecipeDataTable�� ���Ͽ� ������ ���̺� �ش� ��������� �����ϴ��� Ȯ��
	FPlateInitData InitData = UOC2GlobalData::GetPlateMesh(GetWorld(), Ingredients);

	// 3-1. �����͸� ȹ���ϴµ� �����ߴٸ�
	if (nullptr == InitData.StaticMesh) 
	{
		Ingredients.Pop(); // ��� �ڷᱸ������ �����ϰ� ����
		return;
	}
	else // 3-2. �����͸� ȹ���ϴµ� �����ߴٸ� 
	{
		IngredientMesh->SetStaticMesh(InitData.StaticMesh); // �޽� ����
		if (nullptr != IngredientMesh)
		{
			// 3-3. ���� ���� �ö� �丮 �޽� ����
			SetIngredinetMesh(InitData);

			// 3-5. ������ �����ϴ� ���� ���忡�� ����
			Ingredient->RequestOC2ActorDestroy();

			// 4. Texture �߰�
			SetIngredinetTextures(InitData);
			return;
		}
	}
	return;
}

void APlate::SetIngredinetMesh(FPlateInitData Data)
{
	// 1. ���� ��� ����
	SetSimulatePhysics(false); // ������Ʈ�� �浹�� ���ư��� �����̴� ���� �����ϱ� ���� ������ ��� ����.

	// 2. IngredientMesh�� �浹ü�� ������ ����.
	IngredientMesh->AttachToComponent(StaticMeshComponent, FAttachmentTransformRules::KeepRelativeTransform);
	IngredientMesh->SetCollisionProfileName(TEXT("NoCollision"));
	IngredientMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	IngredientMesh->SetSimulatePhysics(false);

	// 3. Offset
	IngredientMesh->SetRelativeLocation(Data.OffsetLocation);
	IngredientMesh->SetRelativeRotation(Data.OffsetRotation);
	IngredientMesh->SetRelativeScale3D(Data.OffsetScale);

	// 4. ���� �ٽ� �Ѱ�
	SetSimulatePhysics(true);
	bIsCombinationSuccessful = true;
}

void APlate::SetIngredinetTextures(FPlateInitData Data)
{
	TArray<UTexture*> Textures = Data.IngredientTextures;
	if (true == Textures.IsEmpty())
	{
		return;
	}

	int32 NumTextures = Textures.Num(); // �ؽ�ó ����
	int32 NumBillboard = TextureBillboards.Num(); // �ؽ�ó �ִ� ���� : 3��(�����ڿ��� ������)
	int32 NumRows = (NumTextures + 1) / 2; // �� ������. (�ø� ó��)

	float BaseZ = 50.0f; // ���� z�� ��ġ
	float VertialSpacing = 40.0f; // ���� ����
	float HorizontalSpacing = 40.0f; // �¿� ����
	for (int32 i = 0; i < NumTextures; i++) // �̹��� ���� �ؽ�ó ����ŭ �ݺ�
	{
		int32 RowIndex = i / 2; 
		int32 ColIndex = i % 2;

		int32 ActualRow = NumRows - 1 - RowIndex; // ���� �� 0������
		float CurrentZ = BaseZ + ActualRow * VertialSpacing; // �� �� ����

		bool bIsRowFull = true;
		// ������ �ؽ�ó�ε� Ȧ����� �� �ؽ�ó�� ����� ����� �ϴϱ�
		if ((RowIndex == NumRows - 1) && (NumTextures % 2 != 0)) 
		{
			bIsRowFull = false; // �ش� ������ �̿��ؼ� 
		}

		float CurrentY = 0.0f;
		if (true == bIsRowFull) // �� �࿡ �� ���� �����ϸ� �¿� ���� ���߰�
		{
			if (0 == ColIndex)
			{
				CurrentY = -HorizontalSpacing / 2.0f;
			}
			else
			{
				CurrentY = HorizontalSpacing / 2.0f;
			}
		}
		else // �� �࿡ ���� �ؽ�ó�� �ϳ��� ��� ������.
		{
			CurrentY = 0.0f;
		}

		FVector NewLocation(0.0f, CurrentY, CurrentZ);

		UTexture2D* Texture = Cast<UTexture2D>(Textures[i]);
		if (nullptr != Texture)
		{
			TextureBillboards[i]->SetSprite(Texture);
			TextureBillboards[i]->bHiddenInGame = false; // �� �Ѹ� �Ⱥ���
			TextureBillboards[i]->SetRelativeLocation(NewLocation);
		}
	}
}
