// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelContent/Table/NonTable/GarbageCan.h"
#include "Global/GameMode/OC2GameMode.h"

AGarbageCan::AGarbageCan()
{

}

void AGarbageCan::BeginPlay()
{
	Super::BeginPlay();
}

void AGarbageCan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGarbageCan::PlaceItem(ACooking* Item)
{
	CookingPtr = Item;
	CookingPtr->AttachToComponent(ComponentForCooking, FAttachmentTransformRules::KeepRelativeTransform);
	CookingPtr->SetActorLocation(ComponentForCooking->GetComponentLocation());

	// Ingredient�� ���ֱ�. Plate�� ��� AOC2Character�� ���
	if (true == CookingPtr->IsCookingType(ECookingType::ECT_INGREDIENT))
	{
		DestroyIngredient(CookingPtr);
	}
}

void AGarbageCan::DestroyIngredient(ACooking* Garbage)
{
	CookingPtr = Garbage;
	/*FQuat Rotation = 
	Garbage->AddActorWorldRotation()*/
	// ...������ ȸ����Ű��...
	
	AOC2GameMode* GM = Cast<AOC2GameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		GM->DestroyOC2Actor(CookingPtr);
		CookingPtr = nullptr;
	}
}