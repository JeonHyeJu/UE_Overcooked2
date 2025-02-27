// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "Global/Data/IngredientDataTable.h"
#include "OC2GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class OVERCOOKED2_API UOC2GameInstance : public UGameInstance
{
	GENERATED_BODY()

	//friend class UGlobla

public:
	UOC2GameInstance();
	~UOC2GameInstance();

	/**
	 * ����� ������ �����ɴϴ�.
	 * 
	 * @param RowName ������ ���̺��� ã�� ���� �̸��Դϴ�.
	 * @return �ش� ����� ����(EIngredientType)�Դϴ�.
	 */
	UFUNCTION(BlueprintCallable)
	EIngredientType GetIngredientType(const FString& RowName);
	/**
	 * Ư�� ����� ���� �����͸� �����ɴϴ�.
	 * 
	 * @param RowName ������ ���̺��� ã�� ���� �̸��Դϴ�.
	 * @return �ش� ����� ���� ������ �迭(TArray<FIngredientCookDataRow>)�Դϴ�.
	 */
	UFUNCTION(BlueprintCallable)
	const TArray<FIngredientCookDataRow>& GetIngredientCookDataRows(const FString& RowName);
	/**
	 * Ư�� ����� ����ƽ �޽ø� �����ɴϴ�.
	 * 
	 * @param RowName ������ ���̺��� ã�� ���� �̸��Դϴ�.
	 * @return �ش� ����� ����ƽ �޽�(UStaticMesh*)�Դϴ�.
	 */
	UFUNCTION(BlueprintCallable)
	UStaticMesh* GetIngredientStaticMesh(const FString& RowName);
	/**
	 * @brief �־��� ��� Ÿ��(EIngredientType)�� �ش��ϴ� ������ ���̺� �� �̸��� ��ȯ�մϴ�.
	 *
	 * @param IngredientType ��ȸ�� ����� Ÿ���Դϴ�.
	 * @return FName �ش� ����� ������ ���̺� �� �̸��� ��ȯ�մϴ�. ��ȿ���� ���� Ÿ���� ��� �� FName("")�� ��ȯ�մϴ�.
	 */
	UFUNCTION(BlueprintCallable, Category = "Ingredients")
	FName GetIngredientDataTableRowName(EIngredientType IngredientType);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	UDataTable* IngredientDataTable = nullptr;
	
};
