// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Global/OC2Enum.h>
#include <Global/Data/IngredientDataTable.h>
#include <Global/OC2GameInstance.h>
#include <Global/GameFramework/OC2Actor.h>
#include <Global/Interface/Interactable.h>
#include "Cooking.generated.h"

// Ingredient(�丮 ���)�� Plate(�丮)�� �ֻ��� Ŭ���� 
UCLASS()
class OVERCOOKED2_API ACooking : public AOC2Actor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACooking();

	const FIngredientDataRow* const GetIngredientDataTable() const
	{
		return IngredientDataTable;
	}
	
	UFUNCTION(BlueprintCallable)
	const ECookingType GetCookingType() const 
	{
		return CookingType;
	}

	UFUNCTION(BlueprintCallable)
	bool IsCookingType(ECookingType Type) const
	{
		return Type == CookingType;
	}

	// ���ø��� BP���� ȣ���� �� ����.
	template<typename T>
	T* GetChild(T* Cooking)
	{
		T* NewCooking = Cast<T>(Cooking);
		return NewCooking;
	}

	// ��Ƽ���� ���̶���Ʈ ȿ�� ����
	UFUNCTION(BlueprintCallable)
	virtual void ApplyMaterialHighlight() {}

	// ��Ƽ���� ���̶���Ʈ ȿ���� ����
	UFUNCTION(BlueprintCallable)
	virtual void RestoreMaterial() {}


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class UTimeEventComponent* TimeEvent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	ECookingType CookingType = ECookingType::ECT_NONE;


	const FIngredientDataRow* IngredientDataTable = nullptr;
private:	
};
