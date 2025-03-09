// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelContent/Cook/Cooking.h"
#include "Pot.generated.h"

UENUM(BlueprintType)
enum class EPotState : uint8
{
	IDLE 		UMETA(DisplayName = "���"),
	BOIL		UMETA(DisplayName = "���� ��"),
	COOKED		UMETA(DisplayName = "���� �Ϸ�"),
	BURNING		UMETA(DisplayName = "Ÿ�� ��"),
	OVERCOOKED	UMETA(DisplayName = "�¿�"),

};

/**
 * 
 */
UCLASS()
class OVERCOOKED2_API APot : public ACooking
{
	GENERATED_BODY()
	
public:
	APot();

	// ó�� ��ᰡ ������ �� ȣ���� �Լ�
	UFUNCTION(BlueprintCallable)
	bool SetBoil(ACooking* Rice);

	// ������ ���� �޾ƿ��� �Լ�
	UFUNCTION(BlueprintCallable)
	class AIngredient* GetCookedIngredient();

	// Pot�� ���� ���̺� ���� ���� �ֳ� �ƴϳ�. �Ź� Table �ʿ��� ĳ���Ϳ� ��ȣ�ۿ��� �� �־���� �ϳ�?
	UFUNCTION(BlueprintCallable)
	void SetOnTable(bool Value)
	{
		bIsOnStove = Value;
	}

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void Cook(float DeltaTime);

	void ChangeAnimation();
	void ChangeMaterialColor();

	bool CanCook();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooking", meta = (AllowprivateAccess = "true"))
	USkeletalMeshComponent* SoupSkeletalMeshComponent = nullptr;

	class AIngredient* Ingredient = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooking", meta = (AllowprivateAccess = "true"))
	EPotState PotState = EPotState::IDLE;

	float TimeElapsed = 0.0f;

	bool bIsOnStove = false;

};
