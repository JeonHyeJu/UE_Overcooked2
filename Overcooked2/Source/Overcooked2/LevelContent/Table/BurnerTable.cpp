// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelContent/Table/BurnerTable.h"
#include <Character/OC2Character.h>
#include <LevelContent/Cook/Pot.h>
#include <Global/OC2Enum.h>

ABurnerTable::ABurnerTable()
{

}

void ABurnerTable::BeginPlay()
{
	Super::BeginPlay();
}

void ABurnerTable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ACooking* ABurnerTable::Interact(AActor* ChefActor)
{
	AOC2Character* Chef = Cast<AOC2Character>(ChefActor);
	ACooking* TempCooking = nullptr;

	if (CookingPtr != nullptr && false == Chef->IsHolding()) // ���� ����, ���� �� ��
	{
		TempCooking = CookingPtr;
		CookingPtr = nullptr;
		return TempCooking;
	}
	else
	{
		return CookingPtr;
	}
}

void ABurnerTable::PlaceItem(ACooking* Item)
{
	ACooking* TempCooking = Item;
	
	if (true == TempCooking->IsCookingType(ECookingType::ECT_POT))
	{
		CookingPtr = TempCooking;

		CookingPtr->AttachToComponent(ComponentForCooking, FAttachmentTransformRules::KeepRelativeTransform);
		CookingPtr->SetActorLocation(ComponentForCooking->GetComponentLocation());

		CookingPtr->SetCookingTable_Implementation(this);
		APot* TempPot = Cast<APot>(CookingPtr);

		//TempPot->SetOnTable(true);
		//������ ���Ĺ��� Boilable�̸� �ٷ� BoilThePot();
	}
}

void ABurnerTable::BoilThePot()
{
	
}