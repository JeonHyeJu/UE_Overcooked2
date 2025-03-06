// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelContent/Table/SpawnTable.h"
#include <Global/Data/IngredientDataTable.h>
#include "Kismet/GameplayStatics.h"

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


AIngredient* ASpawnTable::SpawnIngredient(AActor* ChefActor, EIngredientType IngredientType)
{

	FActorSpawnParameters SpawnParameters; // ������ �����ε� �Լ� ȣ���� ����(ȸ���� �߰�), FActorSpawnParameters ���
	FVector Location = FVector();
	/*if (nullptr != ChefActor)
	{
		Location = GetActorLocation() + FVector(0.0f, 0.0f, 100.0f);
	}*/
	Location = GetActorLocation() + FVector(0.0f, 0.0f, 100.0f);
	FRotator Rotator = FRotator::ZeroRotator;

	AIngredient* NewIngredient = GetWorld()->SpawnActor<AIngredient>(AIngredient::StaticClass(), Location, Rotator, SpawnParameters);
	NewIngredient->Init(IngredientType);
	//��� ���忡 ����, Init

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

	return NewIngredient;
}

ACooking* ASpawnTable::Interact(AActor* ChefActor)
{
	if (false == bOccupied)
	{
		//return SpawnIngredient(ChefActor);
	}

	return nullptr;
}
