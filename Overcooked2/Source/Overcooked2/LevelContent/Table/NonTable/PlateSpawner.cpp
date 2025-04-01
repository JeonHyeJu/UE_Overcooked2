// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelContent/Table/NonTable/PlateSpawner.h"
#include "LevelContent/Cook/Plate.h"

APlateSpawner::APlateSpawner()
{

}

void APlateSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void APlateSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlateSpawner::SetPlate(class APlate* Plate)
{
	CookingPtr = Cast<APlate>(Plate);
	CookingPtr->SetCookingTable_Implementation(this);

	//Cooking�� Attach ��ų��
	CookingPtr->AttachToComponent(ComponentForCooking, FAttachmentTransformRules::KeepRelativeTransform);
	CookingPtr->SetActorLocation(ComponentForCooking->GetComponentLocation());
}

void APlateSpawner::PlaceItem(ACooking* ReceivedCooking)
{
	ACooking* TempCooking = ReceivedCooking;
}