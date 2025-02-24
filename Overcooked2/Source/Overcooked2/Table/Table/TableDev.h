// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TableDev.generated.h"


//enum class EIngredientState
//{
//    OVERCOOKED = -2, // �¿��� ���� ����� �� ����
//    NONE = -1,
//    COOKED, // ���� �ϼ�
//    CHOPPABLE,
//    GRILLABLE,
//    FRYABLE,
//    RICE_READY,
//    //...,
//    MAX
//};
//
//class AIngredient : public AActor
//{
//public:
//    bool IsCooked() const // ���� �Ϸ�
//    {
//        return State == EIngredientState::COOKED;
//    }
//    bool IsChoppable() const
//    {
//        return State == EIngredientState::CHOPPABLE;
//    }
//
//    FString Name;
//    EIngredientState State = EIngredientState::NONE;
//    float CookingTime = 0.0f;
//    float OvercookTime = 0.0f;
//};
//
//class Cook
//{
//public:
//    static void Chop(AIngredient* Ingredient)
//    {
//        // Chopping
//        Ingredient->State = EIngredientState::COOKED;
//    }
//    static void Grill(AIngredient* Ingredient)
//    {
//        // Grilling
//        Ingredient->State = EIngredientState::COOKED;
//    }
//    static void CookingIngredient(AIngredient* Ingredient, std::function<void(AIngredient*)> CookingFunction)
//    {
//        CookingFunction(Ingredient);
//    }
//};
//// Cook::CookingIngredient(Prawn, Chop);
//// Cook::CookingIngredient(Tomato, Grill);
//
//class APlate : public AActor
//{
//private:
//    APlate* Plate;
//};
//
//class ATable : public AActor
//{
//public:
//    void PlacePlate(APlate* Plate)
//    {
//        PlacedPlate = Plate;
//    }
//    void PlaceIngredient(AIngredient* Ingredient)
//    {
//        // �̹� ������ �ִ� �༮�̶� ������ �ȵǸ�???
//        if (nullptr == PlacedPlate || EIngredientState::COOKED == Ingredient->State)
//        {
//            return;
//        }
//        Ingredients.Add(Ingredient);
//    }
//
//private:
//    TArray<AIngredient*> Ingredients;
//    APlate* PlacedPlate;
//};

UCLASS()
class OVERCOOKED2_API ATableDev : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATableDev();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
