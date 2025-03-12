// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"

#include "Global/Data/IngredientDataTable.h"
#include "Global/Data/OrderDataTable.h"

#include "Global/OC2Struct.h"
#include "Global/OC2Enum.h"

#include "OC2GameInstance.generated.h"

class AIngredient;
struct FRecipeDataRow;

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

public: /** ��Ʈ��ũ ���� �޼ҵ� */
	void CreateRoom();
	void JoinRoom(FString IP, APlayerController* Controller);
	void StartGame();

public:
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
	UFUNCTION(BlueprintCallable, Category = "Global|Data")
	FName GetIngredientDataTableRowName(EIngredientType IngredientType);
	/**
	 * Ư�� ����� ������ ���̺� �� �����͸� ���� �Ͽ� �����ɴϴ�.
	 *
	 * @param World ���� ���� ��ü�Դϴ�.
	 * @return FIngredientDataRow �ش� ����� ������ ���̺� �� �������Դϴ�.
	 */
	UFUNCTION(BlueprintCallable, Category = "Global|Data")
	const FIngredientDataRow& GetIngredientDataRow(const FName& RowName);
	/**
	 * Ư�� ����� ������ ���̺� �� �����͸� Ÿ���� ����Ͽ�
	 *
	 * @param World ���� ���� ��ü�Դϴ�.
	 * @return FIngredientDataRow �ش� ����� ������ ���̺� �� �������Դϴ�.
	 */
	const FIngredientDataRow& GetIngredientDataRow(EIngredientType IngredientType);


	UFUNCTION(BlueprintCallable, Reliable, Server)
	void SpawnIngredientActor(EIngredientType IngredientType);

	TArray<FPlateInitData> GetPlateMesh(TArray<FRecipe>& Recipes);
	bool FindRecipe(const FRecipeDataRow* RecipeDataRow, TArray<FRecipe>& Recipes);

public:
	FString GetChefHeadName() const;
	void SetChefHeadName(FString HeadName);

public:
	UPROPERTY(EditAnywhere, Category = "Global|Level")
	TSoftObjectPtr<UWorld> TitleLevel;

	UPROPERTY(EditAnywhere, Category = "Global|Level")
	TSoftObjectPtr<UWorld> LobbyLevel;

	UPROPERTY(EditAnywhere, Category = "Global|Level")
	TSoftObjectPtr<UWorld> WorldLevel;

	UPROPERTY(EditAnywhere, Category = "Global|Level")
	TSoftObjectPtr<UWorld> CookingLevel;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	UDataTable* IngredientDataTable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	UDataTable* OrderDataTable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Data")
	UDataTable* RecipeDataTable = nullptr;

private:
	UPROPERTY(EditAnywhere, Category = "Global|Data")
	FString Port = TEXT("3000");

private:
	UPROPERTY(EditAnywhere, Category = "Global|Character")
	FString ChefHeadName = "";
};
