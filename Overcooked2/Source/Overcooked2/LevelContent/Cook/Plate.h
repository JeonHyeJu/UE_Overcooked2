// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <LevelContent/Cook/Cooking.h>
#include <Global/OC2Enum.h>
//#include <Global/Interface/InterActable.h>
#include "Plate.generated.h"

// ���� ~ ���ÿ� �ö� ������ �丮 ~ �丮���� ���� ~ �ϼ��� �丮
UCLASS()
class OVERCOOKED2_API APlate : public ACooking/*, public UInterActable*/
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlate();

	UFUNCTION(BlueprintCallable)
	void CleanPlate()
	{
		bCanPlaceIngredient = true;
	}

	bool Add(class AIngredient* Ingredient)
	{
		// ����ó�� ���� �ʿ�
		//if (nullptr == Ingredient || Ingredient.GetIngredientState() != EIngredientState::COOKED)
		//{
		//	return false;
		//}

		// TArray�� Add
		return true;
	}
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// TArray�� �־�� �� ��?
	// FCookableIngredient CookedIngredient;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	bool bCanPlaceIngredient = true;
};
