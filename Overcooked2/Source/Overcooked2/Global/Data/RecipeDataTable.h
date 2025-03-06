// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Global/OC2Struct.h"
#include "RecipeDataTable.generated.h"

// ������ ������ ��
USTRUCT(BlueprintType)
struct FRecipeDataRow : public FTableRowBase
{
	GENERATED_BODY()

	FRecipeDataRow() {}
	~FRecipeDataRow() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	UTexture2D* OrderTexutre = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	TArray<FCookableIngredient> RequireIngredients;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	UStaticMesh* FoodMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	FVector OffsetLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	FRotator OffsetRotation = FRotator::ZeroRotator;
};

/**
 * 
 */
UCLASS()
class OVERCOOKED2_API URecipeDataTable : public UObject
{
	GENERATED_BODY()
	
};
