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



	// ���ڿ��� ������ ��
	UFUNCTION(BlueprintCallable)
	AIngredient* Init(EIngredientType Type);

	// ���� �Ϸ� ��, ĳ����(Server RPC �Լ�) -> ���̺� -> ���� ȣ��
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

	UFUNCTION(BlueprintCallable)
	bool IsCooked();


	UFUNCTION(NetMulticast, Reliable)
	void SetThrowing(bool IsThrowing);
	void SetThrowing_Implementation(bool IsThrowing)
	{
		bIsThrowing = IsThrowing;
	}

	bool IsThrowing() const
	{
		return bIsThrowing;
	}


	UFUNCTION(NetMulticast, Reliable)
	void SetThrower(AActor* Actor);
	void SetThrower_Implementation(AActor* Actor)
	{
		Thrower = Actor;
	}

	AActor* GetThrower() const
	{
		return Thrower;
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

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	bool bIsThrowing = false;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	AActor* Thrower = nullptr;

};
