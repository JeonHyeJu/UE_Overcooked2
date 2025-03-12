// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <LevelContent/Cook/Cooking.h>
#include "Ingredient.generated.h"

// �丮 ���
UCLASS()
class OVERCOOKED2_API AIngredient : public ACooking
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIngredient();

	// Network
	UFUNCTION(BlueprintCallable, Reliable, Server)
	void SetType(EIngredientType Type);
	void SetType_Implementation(EIngredientType Type);

	// Interact
	UFUNCTION(NetMulticast, Reliable)
	void AttachToChef(AActor* Player);
	void AttachToChef_Implementation(AActor* Player);

	UFUNCTION(NetMulticast, Reliable)
	void DetachFromChef(AActor* Player);
	void DetachFromChef_Implementation(AActor* Player);

	// ���ڿ��� ������ ��
	UFUNCTION(BlueprintCallable)
	AIngredient* Init(EIngredientType Type);
	
	// ���� �Ϸ� ��
	UFUNCTION(BlueprintCallable, Reliable, NetMulticast)
	void ChangeState(EIngredientState State);
	void ChangeState_Implementation(EIngredientState State);

	// �������� ���� �ϴ� ����?
	UFUNCTION(BlueprintCallable)
	bool IsChoppable() const
	{
		return CurIngredientState == EIngredientState::EIS_CHOPPABLE;
	}

	// �������ҿ� ������ �ϴ� ����?
	UFUNCTION(BlueprintCallable)
	bool IsGrillable() const
	{
		return CurIngredientState == EIngredientState::EIS_GRILLABLE;
	}

	// �ܿ��� ���� ���� �� �־�?
	UFUNCTION(BlueprintCallable)
	bool IsBoilable() const
	{
		return CurIngredientState == EIngredientState::EIS_BOILABLE;
	}

	UFUNCTION(BlueprintCallable)
	EIngredientType GetIngredientType() const 
	{
		return IngredientType;
	}

	UFUNCTION(BlueprintCallable)
	EIngredientState GetCurIngredientState() const
	{
		return CurIngredientState;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	const FIngredientCookDataRow& CheckState(EIngredientState State);

	void Offset(FVector Pos, FRotator Rot);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

private:
	void DeactivateHighlight();
	void ActivateHighlight();


	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	EIngredientType IngredientType = EIngredientType::EIT_NONE;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	EIngredientState CurIngredientState = EIngredientState::EIS_NONE;

};
