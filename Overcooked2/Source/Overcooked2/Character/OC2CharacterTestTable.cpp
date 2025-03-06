// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/OC2CharacterTestTable.h"
#include "Character/OC2Character.h"

// Sets default values
AOC2CharacterTestTable::AOC2CharacterTestTable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	MySceneComponent = CreateDefaultSubobject<USceneComponent>("Attach");
	MySceneComponent->SetupAttachment(RootComponent);

}

AOC2CharacterTestObject* AOC2CharacterTestTable::SpawnIngredient(AActor* ChefActor)
{
	FActorSpawnParameters SpawnParameters; // ������ �����ε� �Լ� ȣ���� ����(ȸ���� �߰�), FActorSpawnParameters ���
	FVector Location = FVector();
	if (nullptr != ChefActor)
	{
		Location = GetActorLocation() + FVector(0.0f, 0.0f, 100.0f);
	}
	FRotator Rotator = FRotator::ZeroRotator;

	// 1. ��Ḧ ���忡 �����Ѵ�.
	// Transform�� ������ �޽õ� ���� �� ������ ����
	AOC2CharacterTestObject* NewIngredient = GetWorld()->SpawnActorDeferred<AOC2CharacterTestObject>(AOC2CharacterTestObject::StaticClass(), FTransform());

	// 2. �޽ø� ã�Ƽ�
	NewIngredient->SetIngredient(IngredientType);

	NewIngredient->FinishSpawning(FTransform());

	return NewIngredient;
}

void AOC2CharacterTestTable::PlaceItem(ACooking* Cook)
{
	CurCook = Cook;
	CurCook->AttachToComponent(MySceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CurCook->SetActorLocation(MySceneComponent->GetComponentLocation());
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

