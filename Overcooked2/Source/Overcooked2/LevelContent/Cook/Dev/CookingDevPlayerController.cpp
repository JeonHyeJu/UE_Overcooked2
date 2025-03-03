// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelContent/Cook/Dev/CookingDevPlayerController.h"
#include <LevelContent/Cook/Dev/CookingDevHUD.h>
#include <LevelContent/Cook/Dev/CookingDevUserWidget.h>

ACookingDevPlayerController::ACookingDevPlayerController()
{
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

ACookingDevPlayerController::~ACookingDevPlayerController()
{
}

void ACookingDevPlayerController::EnableUIMode()
{
	// 1. ���콺 Ŀ���� ���̰�
	SetShowMouseCursor(true);

	// 2. UI��� ����
	FInputModeUIOnly InputMode;
	ACookingDevHUD* CurHUD = Cast<ACookingDevHUD>(GetHUD());
	if (nullptr == CurHUD)
	{
		UE_LOG(LogTemp, Warning, TEXT("HUD�� ã�� ����"));
		return;
	}

	UCookingDevUserWidget* CurWidget = CurHUD->GetWidget();
	if (nullptr != CurWidget)
	{
		InputMode.SetWidgetToFocus(CurWidget->TakeWidget());
	}



	//InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	SetInputMode(InputMode);
}

void ACookingDevPlayerController::BeginPlay()
{
	Super::BeginPlay();
	EnableUIMode();
}

void ACookingDevPlayerController::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
