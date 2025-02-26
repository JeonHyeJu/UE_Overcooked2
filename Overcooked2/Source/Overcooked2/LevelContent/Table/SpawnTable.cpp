// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelContent/Table/SpawnTable.h"
#include <Global/Data/IngredientDataTable.h>

ASpawnTable::ASpawnTable()
{
}

void ASpawnTable::Init(EIngredientType)
{
}

AIngredient* ASpawnTable::SpawnIngredient(EIngredientType Ingredient)
{
	// LoadObject : Ư�� ��ο� �ִ� UObject ��� ���� �ε� �Լ�
	UDataTable* DataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/Blueprints/Global/Data/DT_IngredientDataTable.DT_IngredientDataTable'_C"));

	if (nullptr == DataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("IngredientDataTable�� ã�� ���� ��� ������ �����߽��ϴ�."));
		return nullptr;
	}

	FName RowName = *UEnum::GetValueAsString(Ingredient);
	FIngredientDataRow* IngredientData = DataTable->FindRow<FIngredientDataRow>(RowName, TEXT(""));

	if (nullptr == IngredientData)
	{
		UE_LOG(LogTemp, Warning, TEXT("IngredinetDataTable���� ��� Ÿ�԰� ��ġ�ϴ� �����͸� ���⿡ �����߽��ϴ�."));
		return nullptr;
	}

	FActorSpawnParameters SpawnParameters;
	FVector Location = GetActorLocation();
	// ������ �����ε� �Լ� ȣ���� ����(ȸ����), FActorSpawnParameters ���
	AIngredient* NewIngredient = GetWorld()->SpawnActor<AIngredient>(AIngredient::StaticClass(), Location, FRotator::ZeroRotator, SpawnParameters); 

	if (nullptr == NewIngredient)
	{
		UE_LOG(LogTemp, Warning, TEXT("���� ������ �����߽��ϴ�."));
		return nullptr;
	}
	
	NewIngredient->Init(RowName);

	return NewIngredient;
}
