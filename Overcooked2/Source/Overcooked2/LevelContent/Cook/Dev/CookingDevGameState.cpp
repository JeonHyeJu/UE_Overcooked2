// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelContent/Cook/Dev/CookingDevGameState.h"
#include <LevelContent/Cook/Dev/CookingDevGameMode.h>
#include <Net/UnrealNetwork.h>

ACookingDevGameState::ACookingDevGameState()
{
	bReplicates = true;
}

void ACookingDevGameState::SetIngredientType(EIngredientType Type)
{
	IngredientType = Type;
	RequestSpawnIngredient();
}

void ACookingDevGameState::RequestSpawnIngredient_Implementation()
{
	// ���� ������Ʈ�� �׻� ���Ӹ�带 ������ �� ������? 
	// �������� �������ָ� �������.
	ACookingDevGameMode* GameMode = Cast<ACookingDevGameMode>(GetWorld()->GetAuthGameMode());
	if (nullptr != GameMode)
	{
		GameMode->SpawnIngredient(IngredientType);
	}
}

void ACookingDevGameState::BeginPlay()
{
	Super::BeginPlay();
}

void ACookingDevGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACookingDevGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACookingDevGameState, IngredientType);
}
