// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Global/OC2Enum.h"
#include "OC2Struct.generated.h"

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	UTexture2D* IngredientTexture = nullptr;

};

// ��� ���պ� �޽� ������ �Ӽ�
USTRUCT(BlueprintType)
struct FOrder
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	UTexture2D* OrderTexutre = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	TArray<FCookableIngredient> RequireIngredients;
};

// ���� ������ �丮 �Ӽ�
USTRUCT(BlueprintType)
struct FRecipe
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	EIngredientType IngredientType = EIngredientType::EIT_NONE;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	EIngredientState IngredientState = EIngredientState::EIS_NONE;
};

USTRUCT(BlueprintType)
struct FPlateInitData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	UStaticMesh* StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	FVector OffsetLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	FRotator OffsetRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	FVector OffsetScale = FVector::OneVector;
};

/**
 * 
 */
UCLASS()
class OVERCOOKED2_API UOC2Struct : public UObject
{
	GENERATED_BODY()
	
};
