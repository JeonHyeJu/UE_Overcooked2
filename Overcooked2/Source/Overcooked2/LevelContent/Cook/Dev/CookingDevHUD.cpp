// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelContent/Cook/Dev/CookingDevHUD.h"
#include <LevelContent/Cook/Dev/CookingDevUserWidget.h>
#include <LevelContent/Cook/Dev/CookingDevGameMode.h>
#include <LevelContent/Cook/Dev/SpawnManager.h>

ACookingDevHUD::ACookingDevHUD()
{
}

ACookingDevHUD::~ACookingDevHUD()
{
}

void ACookingDevHUD::ServerSpawnIngredient(EIngredientType Type)
{
	SpawnManager = GetWorld()->SpawnActor<ASpawnManager>(ASpawnManager::StaticClass());
	SpawnManager->SetIngredientType(GetWorld(), Type);
}

void ACookingDevHUD::BeginPlay()
{
	Super::BeginPlay();
	if (nullptr != WidgetSubclass)
	{
		Widget = CreateWidget<UCookingDevUserWidget>(GetWorld(), WidgetSubclass);
		if (nullptr != Widget)
		{
			Widget->AddToViewport();
			//Widget->SetKeyboardFocus();
		}
	}
	HandleUIInput();

	ACookingDevGameMode* GameMode = Cast<ACookingDevGameMode>(GetWorld()->GetAuthGameMode());
	if (nullptr != GameMode)
	{
		GameMode->SetWidget(Widget);
	}
}

void ACookingDevHUD::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ACookingDevHUD::HandleUIInput()
{
	APlayerController* Controller = GetOwningPlayerController();

	// 1. ���콺 Ŀ���� ���̰�
	Controller->SetShowMouseCursor(true);

	// 2. UI��� ����
	FInputModeGameAndUI InputMode;

	if (nullptr != Widget)
	{
		InputMode.SetWidgetToFocus(Widget->TakeWidget());
	}

	Controller->SetInputMode(InputMode);
}
