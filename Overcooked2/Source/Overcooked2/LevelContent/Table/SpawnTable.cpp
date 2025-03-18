// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelContent/Table/SpawnTable.h"
#include <Global/Data/IngredientDataTable.h>
#include "Kismet/GameplayStatics.h"
#include "Global/GameMode/OC2GameMode.h"
#include <Character/OC2Character.h>

ASpawnTable::ASpawnTable()
{
}

void ASpawnTable::BeginPlay()
{
	Super::BeginPlay();

}

void ASpawnTable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawnTable::SetIngredient(EIngredientType IngredientTypeSetting)
{
	IngredientType = IngredientTypeSetting;
}



ACooking* ASpawnTable::Interact(AActor* ChefActor)
{
	AOC2Character* Chef = Cast<AOC2Character>(ChefActor);
	ACooking* TempCooking = nullptr;
	
	if (false == bIsOccupied) // ���̺��� ����ִ�.
	{
		RequestSpawn();
		return SpawnedIngredient;
	}
	else
	{
		//TempCooking = SPlacedItem;
		TempCooking = CookingPtr;
		//PlacedItem�� �ܺ� Cooking�� ��ȣ�ۿ� �ϴ� ���
		// 1. ���� ������ ���
		// 2. �����ÿ� �丮�� �ִ� ������ ���
	}

	return TempCooking;
}

void ASpawnTable::RequestSpawn_Implementation()
{
	auto GM = Cast<AOC2GameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		SpawnedIngredient = GM->SpawnIngredientActor(IngredientType);
	}
}

void ASpawnTable::PlaceItem(ACooking* Item)
{
	CookingPtr = Item;
	
	FVector OnTheTable = GetActorLocation() + FVector{ (0.0f, 0.0f, 100.0f) };
	CookingPtr->SetActorLocation(OnTheTable);
}
