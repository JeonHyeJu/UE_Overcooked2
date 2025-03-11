// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelContent/Cook/Dev/CookingDevUserWidget.h"
#include <LevelContent/Cook/Ingredient.h>
#include "Kismet/GameplayStatics.h"
#include <LevelContent/Cook/Dev/CookingDevGameMode.h>
#include <Global/OC2Global.h>
#include <LevelContent/Cook/Dev/CookingDevGameState.h>
#include <LevelContent/Cook/Dev/CookingDevHUD.h>
#include <levelcontent/Cook/Dev/SpawnManagerComponent.h>
#include <Character/OC2Character.h>

void UCookingDevUserWidget::ServerSpawnIngredient(EIngredientType Type)
{

	// HUD -> SpawnManager -> GameMode
	APlayerController* Controller = GetOwningPlayer();
	if (nullptr != Controller)
	{
		AOC2Character* Pawn = Cast<AOC2Character>(Controller->GetPawn());
		//Pawn->SpawnManager->SetIngredientType(Type);

	}

	// GameState -> GameMode Fail
	//ACookingDevGameState* GameState = Cast<ACookingDevGameState>(GetWorld()->GetGameState());
	//if (nullptr != GameState)
	//{
	//	GameState->SetIngredientType(Type);
	//}


	//ACookingDevGameMode* GameMode = Cast<ACookingDevGameMode>(GetWorld()->GetAuthGameMode());
	//if (nullptr != GameMode)
	//{
	//	GameMode->SpawnIngredient(Type);
	//}
}

void UCookingDevUserWidget::ChangeState(EIngredientState State)
{
	if (true == CookingActor.IsEmpty())
	{
		return;
	}

	for (int i = 0; i < CookingActor.Num(); i++)
	{
		AIngredient* Ingredient = Cast<AIngredient>(CookingActor[i]);
		if (State == Ingredient->GetCurIngredientState())
		{
			return;
		}
		else
		{
			Ingredient->ChangeState(State);
		}
	}
}

void UCookingDevUserWidget::StartServer()
{
	FString OpenLevel = TEXT("");
	FString LevelPath = TEXT(""); // ������ ���� ��θ� ������ ����

	UOC2Global::GetAssetPackageName(UWorld::StaticClass(), TEXT("CookingDevLevel"), LevelPath);
	OpenLevel = FString::Printf(TEXT(":%s%s"), *Port, *LevelPath);
	// :30000/Game/Map/CookingDevLevel

	UGameplayStatics::OpenLevel(GetWorld(), *OpenLevel, true, TEXT("listen"));
}

void UCookingDevUserWidget::Connect()
{
	FString ConnectLevelName = FString::Printf(TEXT("%s:%s"), *IP, *Port);
	// 127.0.0.1:30000

	UGameplayStatics::OpenLevel(GetWorld(), FName(*ConnectLevelName));

	// Debug
	UE_LOG(LogTemp, Warning, TEXT("ConnectLevelName: %s"), *ConnectLevelName);
}
