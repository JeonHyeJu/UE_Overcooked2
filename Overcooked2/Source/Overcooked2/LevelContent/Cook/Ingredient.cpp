// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelContent/Cook/Ingredient.h"

// Sets default values
AIngredient::AIngredient()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Spawn�Ǵ� �༮�� �⺻ ũ�⸦ ��������� �Ѵٸ�?
	//SetActorScale3D(FVector(100.0f, 100.0f, 100.0f));
}

void AIngredient::Init(FName Name)
{
	//StaticMeshComponent->SetStaticMesh()
}

void AIngredient::ChageState(EIngredientState State)
{
}

// Called when the game starts or when spawned
void AIngredient::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIngredient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

