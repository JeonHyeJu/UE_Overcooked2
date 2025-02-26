// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelContent/Table/SpawnTable.h"
#include <Global/Data/IngredientDataTable.h>
#include "Kismet/GameplayStatics.h"

ASpawnTable::ASpawnTable()
{
}


AIngredient* ASpawnTable::SpawnIngredient(FName IngredientName)
{
	//UDataTable* DataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/Blueprints/Global/Data/DT_IngredientDataTable.DT_IngredientDataTable'_C"));

	//if (nullptr == DataTable)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("IngredientDataTable�� ã�� ���� ��� ������ �����߽��ϴ�."));
	//	return nullptr;
	//}

	//FName RowName = *StaticEnum<EIngredientType>()->GetDisplayNameTextByValue(static_cast<int64>(Ingredient)).ToString();
	//FName RowName = *StaticEnum<EIngredientType>()->GetDisplayNameTextByValue(static_cast<int64>(Ingredient)).ToString();
	//FIngredientDataRow* IngredientData = DataTable->FindRow<FIngredientDataRow>(RowName, TEXT(""));

	//if (nullptr == IngredientData)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("IngredinetDataTable���� ��� Ÿ�԰� ��ġ�ϴ� �����͸� ���⿡ �����߽��ϴ�."));
	//	return nullptr;
	//}

	FActorSpawnParameters SpawnParameters; // ������ �����ε� �Լ� ȣ���� ����(ȸ���� �߰�), FActorSpawnParameters ���
	FVector Location = GetActorLocation() + FVector(0.0f, 0.0f, 100.0f); 
	FRotator Rotator = FRotator(90.0f, 90.0f, 90.0f);

	// 1. ��Ḧ ���忡 �����Ѵ�.
	// Transform�� ������ �޽õ� ���� �� ������ ����
	AIngredient* NewIngredient = GetWorld()->SpawnActor<AIngredient>(AIngredient::StaticClass(), Location, Rotator, SpawnParameters);

	if (nullptr == NewIngredient)
	{
		UE_LOG(LogTemp, Warning, TEXT("���� ������ �����߽��ϴ�."));
		return nullptr;
	}
	
	// 2. �޽ø� ã�Ƽ�
	NewIngredient->Init(IngredientName);

	return NewIngredient;
}
