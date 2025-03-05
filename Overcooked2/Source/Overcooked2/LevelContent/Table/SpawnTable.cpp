// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelContent/Table/SpawnTable.h"
#include <Global/Data/IngredientDataTable.h>
#include "Kismet/GameplayStatics.h"

ASpawnTable::ASpawnTable()
{
}

void ASpawnTable::Init(FName Name)
{
	IngredientName = Name;
}

AIngredient* ASpawnTable::SpawnIngredient(AActor* ChefActor)
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
//	NewIngredient->Init(IngredientName);

	return NewIngredient;
}

ACooking* ASpawnTable::Interact(AActor* ChefActor)
{
	if (false == bOccupied)
	{
		return SpawnIngredient(ChefActor);
	}

	return nullptr;
}
