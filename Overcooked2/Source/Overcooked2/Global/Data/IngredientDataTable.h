// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Global/OC2Enum.h"
#include "IngredientDataTable.generated.h"

// ��ħ ������ �����ϴ� ������ �Ӽ�
USTRUCT(BlueprintType)
struct FIngredientCookDataRow 
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	EIngredientState PrevIngredientState = EIngredientState::EIS_NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	EIngredientState IngredientState = EIngredientState::EIS_NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	UStaticMesh* CookMesh = nullptr;
};

// �Ϲ� ��� ������ ��
USTRUCT(BlueprintType)
struct FIngredientDataRow : public FTableRowBase
{
	GENERATED_BODY()

	FIngredientDataRow() {}
	~FIngredientDataRow() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	EIngredientType IngredientType = EIngredientType::EIT_NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	UStaticMesh* BaseMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	TArray<FIngredientCookDataRow> StateRows;
};

// ���� ������ �丮 �Ӽ�
USTRUCT(BlueprintType)
struct FCookableIngredient 
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	EIngredientType IngredientType = EIngredientType::EIT_NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	EIngredientState IngredientState = EIngredientState::EIS_NONE;

};

// ��� ���պ� �޽� ������ �Ӽ�
USTRUCT(BlueprintType)
struct FRecipeMeshDataRow
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	TArray<FCookableIngredient> Array;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	UStaticMesh* BaseMesh = nullptr;
};

// ������ ������ ��
USTRUCT(BlueprintType)
struct FRecipeDataRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	TArray<FCookableIngredient> CookableIngredients;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	TArray<FRecipeMeshDataRow> CheckMesh;
};

// ������������ �����ϴ� ������ ������ ��
USTRUCT(BlueprintType)
struct FStageCookingDataRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	//TArray<FName> StageRecipeNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	// ��¡��
	// ����
	// ��
	// ��
	
	// ����

	TArray<EIngredientType> IngredientType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")

	TArray<FName> AllRecipe;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")

	TArray<int> SelectRecipe;

	// void Init();

};


/**
 * 
 */
UCLASS()
class OVERCOOKED2_API UIngredientDataTable : public UObject
{
	GENERATED_BODY()
	
};
