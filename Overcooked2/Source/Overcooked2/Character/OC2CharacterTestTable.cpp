// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/OC2CharacterTestTable.h"
#include "Character/OC2Character.h"

// Sets default values
AOC2CharacterTestTable::AOC2CharacterTestTable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("MyStaticMesh");
	MySceneComponent= CreateDefaultSubobject<USceneComponent>("Fuck");
	Root = CreateDefaultSubobject<USceneComponent>("DefaultSceneComponent");
	RootComponent = Root;
	StaticMesh->SetupAttachment(RootComponent);
	MySceneComponent->SetupAttachment(RootComponent);

}

AIngredient* AOC2CharacterTestTable::SpawnIngredient(AActor* ChefActor)
{
	//UDataTable* DataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/Blueprints/Global/Data/DT_IngredientDataTable.DT_IngredientDataTable'_C"));

	//if (nullptr == DataTable)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("IngredientDataTable�� ã�� ���� ��� ������ �����߽��ϴ�."));
	//	return nullptr;
	//}

	//FName RowName = *StaticEnum<EIngredientType>()->GetDisplayNameTextByValue(static_cast<int64>(Ingredient)).ToString();
	//FName RowName = *StaticEnum<EIngredientType>()->GetDisplayNameTextByValue(static_cast<int64>(Ingredient)).ToString();
	//FIngredientDataRow* IngredientData = DataTable->FindRow<FIngredientDataRow>(RowName, TEXT(""));

	//if (nullptr == IngredientData)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("IngredinetDataTable���� ��� Ÿ�԰� ��ġ�ϴ� �����͸� ���⿡ �����߽��ϴ�."));
	//	return nullptr;
	//}

	FActorSpawnParameters SpawnParameters; // ������ �����ε� �Լ� ȣ���� ����(ȸ���� �߰�), FActorSpawnParameters ���
	FVector Location = FVector();
	if (nullptr != ChefActor)
	{
		Location = GetActorLocation() + FVector(0.0f, 0.0f, 100.0f);
	}
	FRotator Rotator = FRotator::ZeroRotator;

	// 1. ��Ḧ ���忡 �����Ѵ�.
	// Transform�� ������ �޽õ� ���� �� ������ ����
	AIngredient* NewIngredient = GetWorld()->SpawnActor<AIngredient>(AIngredient::StaticClass(), Location, Rotator, SpawnParameters);

	// ���Ϳ� ����
	if (nullptr != ChefActor)
	{
		//NewIngredient->Interact(ChefActor);
	}

	if (nullptr == NewIngredient)
	{
		UE_LOG(LogTemp, Warning, TEXT("���� ������ �����߽��ϴ�."));
		return nullptr;
	}

	// 2. �޽ø� ã�Ƽ�
	NewIngredient->Init(IngredientType);

	return NewIngredient;
}

void AOC2CharacterTestTable::PlaceItem(ACooking* Cook)
{
	CurCook = Cook;
	CurCook->AttachToComponent(MySceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

ACooking* AOC2CharacterTestTable::Interact(AActor* ChefActor)
{
	AOC2Character* Character = Cast<AOC2Character>(ChefActor);

	if (CurCook == nullptr)
	{
		if (Character->IsHolding())
		{
			return nullptr;
		}
		return SpawnIngredient(ChefActor);

	}
	else
	{
		ACooking* Ret = CurCook;
		CurCook = nullptr;
		return Ret;
	}
}



// Called when the game starts or when spawned
void AOC2CharacterTestTable::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AOC2CharacterTestTable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOC2CharacterTestTable::Highlight()
{
	StaticMesh->SetMaterial(0, HighlightMat);

}

void AOC2CharacterTestTable::OffHighlight()
{
	StaticMesh->SetMaterial(0, OriginMat);

}

