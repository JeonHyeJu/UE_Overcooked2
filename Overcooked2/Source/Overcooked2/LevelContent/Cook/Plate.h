// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <LevelContent/Cook/Cooking.h>
#include <Global/OC2Enum.h>

#include "Plate.generated.h"

// 접시 ~ 접시에 올라간 조리된 요리 ~ 요리들의 조합 ~ 완성된 요리
UCLASS()
class OVERCOOKED2_API APlate : public ACooking
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlate();

	// 접시 위에 재료를 쌓는 모든 과정
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void Add(class AIngredient* Ingredient);
	void Add_Implementation(class AIngredient* Ingredient);

	bool IsCombinationSuccessful() const
	{
		return bIsCombinationSuccessful;
	}


	UFUNCTION(BlueprintCallable)
	bool IsDirtyPlate();

	// 서버(GameMode)에서 호출해야만 적용되는 함수들!!!
	// 설거지 성공 시 호출
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void WashPlate();
	void WashPlate_Implementation();

	// 접시의 상태를 Dirty로 바꿔서 스폰하고 싶으면 호출
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void SetPlateState(EPlateState State);
	void SetPlateState_Implementation(EPlateState State);

	// 접시 위에 요리 재료를 버리고 접시를 초기 상태로 되돌림
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void CleanPlate();
	void CleanPlate_Implementation();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	bool CanPlaceOnPlate(AIngredient* Ingredient);
	void SetIngredinetMesh(FPlateInitData Data);
	void SetIngredinetTextures(FPlateInitData Data);

	void SetMesh();
	void SetMaterialTexture(UTexture* Texture);

	virtual void ForwardAttachToChef() override;
	virtual void ForwardDetachToChef() override;

private:
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	TArray<FRecipe> Ingredients;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* IngredientMesh = nullptr; // 재료

	// 접시 상태
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	EPlateState PlateState = EPlateState::EMPTY;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	UTexture* CleanTexture = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	UTexture* DirtyTexture = nullptr;

	UPROPERTY(Replicated)
	bool bIsCombinationSuccessful = false;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
	TArray<class UBillboardComponent*> TextureBillboards;

};
