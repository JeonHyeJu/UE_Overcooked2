// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/GameMode/OC2GameMode.h"
#include "Overcooked2.h"

#include "Global/Component/SpawnManageComponent.h"
#include "Global/GameFramework/OC2Actor.h"

#include "LevelContent/Cook/Ingredient.h"
#include "LevelContent/Cook/Plate.h"

AOC2GameMode::AOC2GameMode()
{
	SpawnManager = CreateDefaultSubobject<USpawnManageComponent>(TEXT("SpawnManager"));
}

void AOC2GameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AOC2GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOC2GameMode::PostLogin(APlayerController* NewPlayerController)
{
	Super::PostLogin(NewPlayerController);
}

AIngredient* AOC2GameMode::SpawnIngredientActor(EIngredientType IngredientType)
{
	if (nullptr != IngredientToSpawn)
	{
		return SpawnManager->SpawnIngredientActor(IngredientToSpawn, IngredientType);
	}
	else
	{
		UE_LOG(OVERCOOKED_LOG, Error, TEXT("Ingredient BP Spawn actor is nullptr BP_CookingGameMode"));
		return nullptr;
	}
}

APlate* AOC2GameMode::SpawnPlateActor(EPlateState PlateState)
{
	if (nullptr != PlateToSpawn)
	{
		return SpawnManager->SpawnPlateActor(PlateToSpawn, PlateState);
	}
	else
	{
		UE_LOG(OVERCOOKED_LOG, Error, TEXT("Plate BP Spawn actor is nullptr BP_CookingGameMode"));
		return nullptr;
	}
}

void AOC2GameMode::DestroyOC2Actor(AOC2Actor* OC2Actor)
{
	OC2Actor->Destroy();
}
