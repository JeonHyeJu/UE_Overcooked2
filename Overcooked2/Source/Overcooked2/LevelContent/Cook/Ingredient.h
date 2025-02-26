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

	// �����ڿ��� �⺻���� �����͸� �Է��ϰ� �ؾ��ϳ�? �Ƹ���?
	AIngredient(const FString& Name, EIngredientType Type, EIngredientState State, float CookingDuration, float OverCookDuration = 0.0f)
	{
		IngredientName = Name;
		IngredientType = Type;
		IngredientState = State;
		CookingTime = CookingDuration; 
		if (0.0f < OverCookDuration)
		{
			bCanOvercook = true;
			OvercookTime = OverCookDuration;
		}
	}
	
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	FString IngredientName = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	EIngredientType IngredientType = EIngredientType::EFD_NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	EIngredientState IngredientState = EIngredientState::EFS_NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	float CookingTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	float OvercookTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	bool bCanOvercook = false;

};
