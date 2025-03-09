// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelContent/Table/SpawnTable.h"
#include <Global/Data/IngredientDataTable.h>
#include "Kismet/GameplayStatics.h"
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


AIngredient* ASpawnTable::SpawnIngredient(AActor* ChefActor/*, EIngredientType IngredientType*/)
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
	AOC2Character* Chef = Cast<AOC2Character>(ChefActor);
	ACooking* TempCooking = nullptr;
	
	if (false == bIsOccupied)
	{
		if (true == Chef->IsHolding())
		{
			// �ڽ� ���� ����ְ� ������ ���𰡸� ��� �ִ�. 
			PlaceItem(TempCooking);
		}
		else
		{
			SpawnIngredient(ChefActor);
		}
	}
	else
	{
		// �ڽ� ���� ���𰡰� ����
		return PlacedItem;

		//PlacedItem�� �ܺ� Cooking�� ��ȣ�ۿ� �ϴ� ���
		// 1. ���� ������ ���
		// 2. �����ÿ� �丮�� �ִ� ������ ���
	}

}

void ASpawnTable::PlaceItem(ACooking* Item)
{
	ACooking* TempCooking = Item;
	
	/*ECookingType TempCookingType = TempCooking->GetCookingType();

	if (ECookingType::ECT_INGREDIENT == TempCookingType)
	{

	}
	else
	{

	}*/
}
