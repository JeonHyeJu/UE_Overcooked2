// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Overcooked2.h"
#include <LevelContent/Cook/Ingredient.h>
#include <LevelContent/Cook/Plate.h>
#include <Global/OC2GameInstance.h>
#include <Global/GameFramework/OC2Actor.h>
#include <Global/Interface/Interactable.h>
#include "CookingTable.generated.h"

UCLASS()
class OVERCOOKED2_API ACookingTable : public AOC2Actor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACookingTable();

	virtual void Interact(AActor* ChefActor) override {}

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	float CookingTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	float OvercookTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	bool bCanOvercook = false;

};
