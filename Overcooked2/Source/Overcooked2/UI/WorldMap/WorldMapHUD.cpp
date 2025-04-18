// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WorldMap/WorldMapHUD.h"
#include "UI/WorldMap/UI/WorldMapUserWidget.h"
#include "UI/Loading/LoadingWidget.h"
#include "Overcooked2.h"

void AWorldMapHUD::BeginPlay()
{
	Super::BeginPlay();

	WorldMapUserWidget = Cast<UWorldMapUserWidget>(CreateWidget(GetWorld(), WorldWidgetObject));
	LoadingWidget = Cast<ULoadingWidget>(CreateWidget(GetWorld(), LoadingWidgetObject));

	if (WorldMapUserWidget == nullptr || LoadingWidget == nullptr)
	{
		UE_LOG(OVERCOOKED_LOG, Error, TEXT("����� ���� Ȥ�� �ε� ������ nullptr �Դϴ�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));
	}

	WorldMapUserWidget->AddToViewport();
	LoadingWidget->AddToViewport();
	LoadingWidget->SetVisibility(ESlateVisibility::Hidden);
}


void AWorldMapHUD::ShowLoadingWidget()
{
	LoadingWidget->SetVisibility(ESlateVisibility::Visible);
	LoadingWidget->PlayZoomOutAnimation();
}