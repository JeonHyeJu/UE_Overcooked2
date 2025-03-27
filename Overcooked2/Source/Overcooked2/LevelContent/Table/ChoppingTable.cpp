// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelContent/Table/ChoppingTable.h"
#include <Character/OC2Character.h>
#include <Global/OC2Enum.h>

AChoppingTable::AChoppingTable()
{
	
}

void AChoppingTable::BeginPlay()
{
	Super::BeginPlay();
}

void AChoppingTable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (true == bTimerActivated)
	{
		TimerUpdate(DeltaTime);

		if (Timer < 0)
		{
			bChoppingDone = true;
		}
	}

	if (bChoppingDone == true)
	{
		ChoppingIsDone();
	}
}

ACooking* AChoppingTable::Interact(AActor* ChefActor)
{
	ChefPtr = Cast<AOC2Character>(ChefActor);
	ACooking* TempCooking = nullptr;

	if (CookingPtr != nullptr && false == ChefPtr->IsHolding()) // ���� ����, ���� �� ��
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

void AChoppingTable::ChopIngredient(AActor* ChefActor)
{
	if (nullptr != ChefActor && nullptr != CookingPtr)
	{
		if (true == CookingPtr->IsCookingType(ECookingType::ECT_INGREDIENT))
		{
			AIngredient* PlacedIngredient = Cast<AIngredient>(CookingPtr);

			//if (true == PlacedIngredient->IsChoppable())
			{
				Timer = 2.0f;
				bTimerActivated = true;
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Magenta, "Chopping...");
			}
		}
	}
}

void AChoppingTable::ChoppingIsDone()
{
	bTimerActivated = false;

	AIngredient* PlacedIngredient = Cast<AIngredient>(CookingPtr);
	PlacedIngredient->ChangeState(EIngredientState::EIS_CHOPPED);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Turquoise, "Chopping Done");
	CookingPtr = Cast<ACooking>(PlacedIngredient);

	ChefPtr->Chopping(false);
	ChefPtr = nullptr;
	bChoppingDone = false;
}

void AChoppingTable::TimerUpdate(float DeltaTime)
{
	Timer -= DeltaTime;
	CurTime = Timer;
}

