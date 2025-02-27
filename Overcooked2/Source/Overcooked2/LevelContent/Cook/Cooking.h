// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Global/OC2Enum.h>
#include <Global/Data/IngredientDataTable.h>
#include <Global/OC2GameInstance.h>
#include <Global/Interface/Interactable.h>
#include "Cooking.generated.h"

// Ingredient(�丮 ���)�� Plate(�丮)�� �ֻ��� Ŭ���� 
UCLASS()
class OVERCOOKED2_API ACooking : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACooking();

	// ĳ���Ϳ� ��ȣ�ۿ��� �Լ�
	// �ݵ�� Ingredient�� Plate���� �������ؾ� ��
	virtual void Interact(AActor* ChefActor) override;

	UFUNCTION(BlueprintCallable)
	bool IsInteracting() const
	{
		return bIsInteracting;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class UTimeEventComponent* TimeEvent = nullptr;

	// ��ȣ�ۿ� ���ΰ�?
	bool bIsInteracting = false; 

private:	
	ECookingType CookingType = ECookingType::ECT_NONE;
};
