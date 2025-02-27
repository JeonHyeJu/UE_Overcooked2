// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <LevelContent/Cook/Cooking.h>
#include <Global/OC2Enum.h>

#include "Plate.generated.h"

// ���� ~ ���ÿ� �ö� ������ �丮 ~ �丮���� ���� ~ �ϼ��� �丮
UCLASS()
class OVERCOOKED2_API APlate : public ACooking
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlate();


	UFUNCTION(BlueprintCallable)
	void CleanPlate();

	// ���� ���� ��Ḧ �״� ��� ����
	UFUNCTION(BlueprintCallable)
	bool Add(class AIngredient* Ingredient);


	void CookCheck();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	const FStageCookingDataRow* Data;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	TArray<class AIngredient*> Ingredients;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* IngredientMesh = nullptr; // ���

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PlateMesh = nullptr; // ����

	

};
