// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby/LobbyGameMode.h"
#include "Overcooked2.h"

#include "Global/OC2GameInstance.h"
#include "Global/OC2Global.h"
#include "Global/OC2Const.h"

ALobbyGameMode::ALobbyGameMode()
{
	ChefHeadNames.Add(UOC2Const::ChefEagleHeadName);
	ChefHeadNames.Add(UOC2Const::ChefMouseHeadName);
	ChefHeadNames.Add(UOC2Const::ChefPandaHeadName);
	ChefHeadNames.Add(UOC2Const::ChefPigHeadName);
}

void ALobbyGameMode::BeginPlay()
{
	Super::BeginPlay();

	//UOC2GameInstance* GameInstance = Cast<UOC2GameInstance>(GetGameInstance());

	//if (GameInstance != nullptr)
	//{
	//	UE_LOG(LogTemp, Log, TEXT("GameInstance �������� ����!"));

	//	GameInstance->SetChefHeadName(ChefHeadNames[CurIdx]);
	//	CurIdx++;
	//}

}

void ALobbyGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayerController)
{
	Super::PostLogin(NewPlayerController);

	PlayerControllers.Push(NewPlayerController);

	// GameInstance ��������
	UOC2GameInstance* GameInstance = Cast<UOC2GameInstance>(NewPlayerController->GetGameInstance());

	if (GameInstance != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("GameInstance �������� ����!"));

		GameInstance->SetChefHeadName(ChefHeadNames[CurIdx]);
		CurIdx++;
	}
}

void ALobbyGameMode::EntryStay()
{
}

void ALobbyGameMode::Stay(float DeltaTime)
{
}
