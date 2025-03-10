// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <LevelContent/Cook/Cooking.h>
#include <Global/OC2Enum.h>

#include "Plate.generated.h"

UENUM(BlueprintType)
enum class EPlateState : uint8
{
	NONE,
	EMPTY,
	OCCUPIED,
	COMPLETED,
	DIRTY,
};

// ���� ~ ���ÿ� �ö� ������ �丮 ~ �丮���� ���� ~ �ϼ��� �丮
UCLASS()
class OVERCOOKED2_API APlate : public ACooking
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlate();

	// ���� ���� ��Ḧ �״� ��� ����
	UFUNCTION(BlueprintCallable)
	bool Add(class AIngredient* Ingredient);

	UFUNCTION(BlueprintCallable)
	bool IsDirtyPlate();


	// ������ ���� �� ȣ��
	UFUNCTION(BlueprintCallable)
	void WashPlate();

	UFUNCTION(BlueprintCallable)
	void SetPlateState(EPlateState State);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LoadDataTable(class AIngredient* Ingredient);

	void CheckAndChangeState(class AIngredient* Ingredient);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

private:
	TArray<FIngredientCookDataRow> CookingDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	TArray<class AIngredient*> Ingredients;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* IngredientMesh = nullptr; // ���

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	EPlateState PlateState = EPlateState::NONE;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	EIngredientState PrveState = EIngredientState::EIS_NONE;

};
