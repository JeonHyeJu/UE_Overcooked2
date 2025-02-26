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

	// BP���� ������ DishMeshes�� �ε����� �ٲ㼭 �ٸ� �޽ø� ���
	UFUNCTION(BlueprintCallable, Category = "Cooking")
	void SetMeshByIndex(int32 Index);

	// ������ �Լ�, 2�� �ڿ� �ش� �ε����� �޽÷� �ٲ��.
	UFUNCTION(BlueprintCallable, Category = "Cooking")
	void SetDebugMeshByIndex(int32 Index);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// �޽� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TArray<UStaticMesh*> DishMeshes;

	// ���� ���� ���̴� �޽�
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DishMeshComponent;

	class UTimeEventActorComponent* TimeEvent = nullptr;

private:	
	// ECookingType CookingType = ECookingType::NONE;
};
