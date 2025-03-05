// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Global/OC2Enum.h"
#include "Global/Data/IngredientDataTable.h"
#include "OrderDataTable.generated.h"

// ��� ���պ� �޽� ������ �Ӽ�
USTRUCT(BlueprintType)
struct FOrder
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	UTexture2D* OrderTexutre = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	EIngredientType IngredientType = EIngredientType::EIT_NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	TArray<FCookableIngredient> RequireIngredients;
};

// �ֹ� ������ ��
USTRUCT(BlueprintType)
struct FOrderDataRow : public FTableRowBase
{
	GENERATED_BODY()

	FOrderDataRow() {}
	~FOrderDataRow() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	EIngredientType IngredientType = EIngredientType::EIT_NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	TArray<FCookableIngredient> RequireIngredients;
};

/**
 * 
 */
UCLASS()
class OVERCOOKED2_API UOrderDataTable : public UObject
{
	GENERATED_BODY()
	
};
