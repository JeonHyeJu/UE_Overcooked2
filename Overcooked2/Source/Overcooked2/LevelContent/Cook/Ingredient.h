// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <LevelContent/Cook/Cooking.h>
#include <Global/OC2Enum.h>
//#include <Global/Interface/InterActable.h>
#include "Ingredient.generated.h"

// �丮 ���
UCLASS()
class OVERCOOKED2_API AIngredient : public ACooking/*, public UInterActable*/
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIngredient();

	// ���ڿ��� ������ ��
	UFUNCTION(BlueprintCallable)
	void Init(FName Name);
	
	//UFUNCTION(BlueprintCallable)
	//const FIngredientCookDataRow* CheckState(EIngredientState IngredientState);

	UFUNCTION(BlueprintCallable)
	void ChageState(EIngredientState State);


	// ������ ���� ����?
	UFUNCTION(BlueprintCallable)
	bool IsCooked() const 
	{
		return IngredientState == EIngredientState::EFS_COOKED;
	}

	// �������� ���� �ϴ� ����?
	UFUNCTION(BlueprintCallable)
	bool IsChoppable() const
	{
		return IngredientState == EIngredientState::EFS_CHOPPABLE;
	}

	// �������ҿ� ������ �ϴ� ����?
	UFUNCTION(BlueprintCallable)
	bool IsGrillable() const
	{
		return IngredientState == EIngredientState::EFS_GRILLABLE;
	}

	// �ܿ��� ���� ���� �� �־�?
	UFUNCTION(BlueprintCallable)
	bool IsBoilable() const
	{
		return IngredientState == EIngredientState::EFS_BOILABLE;
	}

	UFUNCTION(BlueprintCallable)
	EIngredientType GetIngredientType() const 
	{
		return IngredientType;
	}

	UFUNCTION(BlueprintCallable)
	EIngredientState GetIngredientState() const
	{
		return IngredientState;
	}

	//FIngredientDataRow* const GetDataTable() const
	//{
	//	return DataTable;
	//}

	UStaticMeshComponent* const GetStaticMeshComponent() const
	{
		return StaticMeshComponent;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	//const FIngredientDataRow* DataTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	EIngredientType IngredientType = EIngredientType::EFD_NONE;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	EIngredientState IngredientState = EIngredientState::EFS_NONE;
};
