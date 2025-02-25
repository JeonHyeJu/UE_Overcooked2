// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include <Global/Interface/InterActable.h>
#include "Ingredient.generated.h"

// �丮 ���
UCLASS()
class OVERCOOKED2_API AIngredient : public AActor, /*public UInterActable*/
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIngredient();

	// �����ڿ��� �⺻���� �����͸� �Է��ϰ� �ؾ��ϳ�?
	
	// ������ ���� ����?
	UFUNCTION(BlueprintCallable)
	bool IsCooked() const 
	{
		//return IngredientState == EIngredientState::COOKED;
		return false;
	}

	// �������� ���� �ϴ� ����?
	UFUNCTION(BlueprintCallable)
	bool IsChoppable() const
	{
		//return IngredientState == EIngredientState::CHOPPABLE;
		return false;
	}

	// �������ҿ� ������ �ϴ� ����?
	UFUNCTION(BlueprintCallable)
	bool IsGrillable() const
	{
		//return IngredientState == EIngredientState::GRILLABLE;
		return false;
	}

	// �ܿ��� ���� ���� �� �־�?
	UFUNCTION(BlueprintCallable)
	bool IsBoilable() const
	{
		//return IngredientState == EIngredientState::BOILABLE;
		return false;
	}


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cook", meta = (AllowPrivateAccess = "true"))
	FString Name = TEXT("");

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cook", meta = (AllowPrivateAccess = "true"))
	//EIngredientState IngredientState = EIngredientState::NONE;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cook", meta = (AllowPrivateAccess = "true"))
	//EIngredientType IngredientType = EIngredientType::NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cook", meta = (AllowPrivateAccess = "true"))
	float CookingTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cook", meta = (AllowPrivateAccess = "true"))
	float OvercookTime = 0.0f;

};
