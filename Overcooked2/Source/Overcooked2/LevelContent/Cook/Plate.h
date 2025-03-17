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

	// ���� ���� ��Ḧ �״� ��� ����
	UFUNCTION(BlueprintCallable)
	bool Add(class AIngredient* Ingredient);


	UFUNCTION(BlueprintCallable)
	bool IsDirtyPlate();

	// ����(GameMode)���� ȣ���ؾ߸� ����Ǵ� �Լ���!!!
	// ������ ���� �� ȣ��
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void WashPlate();
	void WashPlate_Implementation();

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void SetPlateState(EPlateState State);
	void SetPlateState_Implementation(EPlateState State);
	// ------------------------------------------------------

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	void SetMesh();
	void SetMaterialTexture(UTexture* Texture);

private:
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	TArray<class AIngredient*> Ingredients;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* IngredientMesh = nullptr; // ���

	// ���� ����
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	EPlateState PlateState = EPlateState::EMPTY;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	UTexture* CleanTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	UTexture* DirtyTexture;

	UPROPERTY(Replicated)
	FVector Position = FVector::ZeroVector;

	UPROPERTY(Replicated)
	FRotator Rotation = FRotator::ZeroRotator;
};
