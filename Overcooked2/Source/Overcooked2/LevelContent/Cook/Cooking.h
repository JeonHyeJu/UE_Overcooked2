// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cooking.generated.h"

// Ingredient(�丮 ���)�� Plate(�丮)�� �ֻ��� Ŭ���� 
UCLASS()
class OVERCOOKED2_API ACooking : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACooking();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//class UTimeEventActorComponent* TimeEvent = nullptr;

private:	
	// ECookingType CookingType = ECookingType::NONE;
};
