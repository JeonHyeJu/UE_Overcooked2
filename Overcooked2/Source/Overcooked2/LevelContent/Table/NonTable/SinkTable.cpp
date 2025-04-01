// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelContent/Table/NonTable/SinkTable.h"
#include "LevelContent/Cook/Plate.h"

ASinkTable::ASinkTable()
{

}

void ASinkTable::BeginPlay()
{
	Super::BeginPlay();
}

void ASinkTable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASinkTable::PlaceItem(ACooking* ReceivedCooking)
{
	if (ECookingType::ECT_PLATE == ReceivedCooking->GetCookingType())
	{
		APlate* TempPlate = Cast<APlate>(ReceivedCooking);
		if (true == TempPlate->IsDirtyPlate())
		{
			// ���ø� ��ũ�뿡 ���´�.
		}
	}
}

void ASinkTable::DoTheDishes()
{

}
