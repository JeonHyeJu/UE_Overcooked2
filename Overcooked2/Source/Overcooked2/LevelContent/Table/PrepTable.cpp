// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelContent/Table/PrepTable.h"

APrepTable::APrepTable()
{

}

void APrepTable::BeginPlay()
{
	Super::BeginPlay();
}

void APrepTable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ACooking* APrepTable::Interact(AActor* ChefActor)
{
	return PPlacedItem;
}

// ACooking�� AIngredient���� APlate���� Ȯ�� �����ؾ� �Ѵ�.
// 
//void APrepTable::SetAndSpawnCooking(AActor* ChefActor, ACooking* CookingObj)
//{
//	FVector CookingObjPos = FVector::ZAxisVector * 100.0f;
//	ACooking* NewCookingObj = CookingObj;
//	NewCookingObj = GetWorld()->SpawnActor<ACooking>();
//	NewCookingObj->SetActorLocation(CookingObjPos);
//}

void APrepTable::PlaceItem(ACooking* Item)
{
	/*ECookingType TempCookingType = TempCooking->GetCookingType();

	if (ECookingType::ECT_INGREDIENT == TempCookingType)
	{

	}
	else
	{

	}*/

	//Cooking ���� �� ����, ���̺� ���� ��ġ
}

void APrepTable::SetAndSpawnCooking(AActor* ChefActor, EIngredientType IngredientType)
{

}
