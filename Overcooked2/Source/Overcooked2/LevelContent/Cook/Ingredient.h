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


	// ���ڿ��� ������ ��
	UFUNCTION(BlueprintCallable)
	void Init(EIngredientType Type); 
	
	UFUNCTION(BlueprintCallable)
	void ChangeState(EIngredientState State);



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

	// �޽ø� �ش� �Լ��� ȣ���Ͽ� �ٲٴ� ���� ����, ChageState �Լ��� ����Ͽ� ���� ������� �޽ø� �����Ϳ��� ã�ƿ� �ٲ� ��
	UFUNCTION(BlueprintCallable)
	UStaticMeshComponent* GetStaticMeshComponent()
	{
		return StaticMeshComponent;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	const FIngredientCookDataRow& CheckState(EIngredientState State);

	void Offset();

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	EIngredientType IngredientType = EIngredientType::EIT_NONE;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	EIngredientState CurIngredientState = EIngredientState::EIS_NONE;
};
