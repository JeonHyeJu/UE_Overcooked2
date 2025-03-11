// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelContent/Cook/Dev/CookingDevGameMode.h"
#include <LevelContent/Cook/Ingredient.h>
#include <LevelContent/Cook/Dev/CookingDevHUD.h>
#include <LevelContent/Cook/Dev/CookingDevUserWidget.h>
#include <Global/OC2Global.h>

ACookingDevGameMode::ACookingDevGameMode()
{
}

void ACookingDevGameMode::SpawnIngredient(EIngredientType Type)
{
	// 2. �������� �����Ѵ�.
	//UWorld* World = GetWorld();
	FTransform Trans;
	AIngredient* Ingredient = GetWorld()->SpawnActorDeferred<AIngredient>(AIngredient::StaticClass(), Trans);
	
	// 3. ���忡 �����Ͽ� BeginPlay ȣ�� ���� �⺻ ������ ���ش�.
	Ingredient->SetType(Type);

	FVector Location = FVector(0.0f, 0.0f, 100.0f);
	Trans.SetLocation(Location);

	Ingredient->FinishSpawning(Trans); // 4. BeginPlay ȣ��

	//AIngredient* Ingredient = UOC2Global::SpawnIngredientActor(GetWorld(), Type);

	if (nullptr != Widget)
	{
		Widget->AddTargetActor(Ingredient);
	}

}

void ACookingDevGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ACookingDevGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
