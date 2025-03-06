// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Global/OC2Struct.h"
#include "Global/OC2Enum.h"

#include "Global/Data/IngredientDataTable.h"
#include "Global/Data/OrderDataTable.h"

#include "OC2GlobalData.generated.h"

class AIngredient;

/**
 * 
 */
UCLASS()
class OVERCOOKED2_API UOC2GlobalData : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * ����� ������ �����ɴϴ�.
	 *
	 * @param RowName ������ ���̺��� ã�� ���� �̸��Դϴ�.
	 * @return �ش� ����� ����(EIngredientType)�Դϴ�.
	 */
	UFUNCTION(BlueprintCallable)
	static EIngredientType GetIngredientType(UWorld* World, const FName& RowName);
	/**
	 * Ư�� ����� ���� �����͸� �����ɴϴ�.
	 *
	 * @param RowName ������ ���̺��� ã�� ���� �̸��Դϴ�.
	 * @return �ش� ����� ���� ������ �迭(TArray<FIngredientCookDataRow>)�Դϴ�.
	 */
	UFUNCTION(BlueprintCallable)
	static const TArray<FIngredientCookDataRow>& GetIngredientCookDataRows(UWorld* World, const FName& RowName);
	/**
	 * Ư�� ����� ����ƽ �޽ø� �����ɴϴ�.
	 *
	 * @param RowName ������ ���̺��� ã�� ���� �̸��Դϴ�.
	 * @return �ش� ����� ����ƽ �޽�(UStaticMesh*)�Դϴ�.
	 */
	UFUNCTION(BlueprintCallable)
	static UStaticMesh* GetIngredientStaticMesh(UWorld* World, const FName& RowName);
	/**
	 * �־��� ��� Ÿ��(EIngredientType)�� �ش��ϴ� ������ ���̺� �� �̸��� ��ȯ�մϴ�.
	 *
	 * @param IngredientType ��ȸ�� ����� Ÿ���Դϴ�.
	 * @return FName �ش� ����� ������ ���̺� �� �̸��� ��ȯ�մϴ�. ��ȿ���� ���� Ÿ���� ��� �� FName("")�� ��ȯ�մϴ�.
	 */
	UFUNCTION(BlueprintCallable, Category = "Global|Data")
	static FName GetIngredientDataTableRowName(UWorld* World, EIngredientType IngredientType);
	/**
	 * Ư�� ����� ������ ���̺� �� �������� �ּҰ��� �����ɴϴ�.
	 *
	 * @param World ���� ���� ��ü�Դϴ�.
	 * @return FIngredientDataRow �ش� ����� ������ ���̺� �� �������Դϴ�.
	 */
	UFUNCTION(BlueprintCallable, Category = "Global|Data")
	static const FIngredientDataRow& GetIngredientDataRow(UWorld* World, const FName& RowName);

	static const FIngredientDataRow& GetIngredientDataRow(UWorld* World, EIngredientType IngredientType);

	static TArray<FPlateInitData> GetPlateMesh(UWorld* World, TArray<FRecipe>& Recipes);

	static TArray<FPlateInitData> GetPlateMesh(UWorld* World, const TArray<class AIngredient*>& Ingredients);
};
