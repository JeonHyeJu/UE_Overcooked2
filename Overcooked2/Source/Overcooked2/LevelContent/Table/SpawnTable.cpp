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

	if (CookingPtr == nullptr && false == Chef->IsHolding()) // ���̺��� ����ִ�.
	{
		RequestSpawn();
		return SpawnedIngredient;
	}
	else
	{
		TempCooking = CookingPtr;
		CookingPtr = nullptr;
	
		return TempCooking;
	}

}

void ASpawnTable::RequestSpawn_Implementation()
{
	auto GM = Cast<AOC2GameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		SpawnedIngredient = GM->SpawnIngredientActor(IngredientType);
	}
}
