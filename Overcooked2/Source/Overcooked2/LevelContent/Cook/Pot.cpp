// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelContent/Cook/Pot.h"
#include <LevelContent/Cook/Ingredient.h>
#include <LevelContent/Table/BurnerTable.h>

APot::APot()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetReplicateMovement(true);

	CookingType = ECookingType::ECT_POT;

	SoupSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SoupSkeletalMeshComponent"));
	SoupSkeletalMeshComponent->SetupAttachment(StaticMeshComponent);

	FVector Pos = FVector(249, 1452, 60);
	StaticMeshComponent->SetRelativeLocation(Pos);
}

void APot::BeginPlay()
{
	ACooking::BeginPlay();

}

void APot::Tick(float DeltaTime)
{
	ACooking::Tick(DeltaTime);
	Cook(DeltaTime);
	ChangeAnimation();
	ChangeMaterialColor();
}

void APot::Cook(float DeltaTime)
{
	if (false == bIsBoiling)
	{
		return;
	}
	TimeElapsed += DeltaTime;
}

void APot::ChangeAnimation()
{
	if (nullptr == Ingredient)
	{
		return;
	}

	switch (PotState)
	{
	case EPotState::IDLE:
		break;
	case EPotState::BOILING:
		break;
	case EPotState::COOKED:
		break;
	case EPotState::OVERCOOKED:
		break;
	default:
		break;
	}
}

void APot::ChangeMaterialColor()
{
}

// Pot�� ������ �� ��� ����� �������°�?
bool APot::CanCook()
{

	if (nullptr == Ingredient) // 2. ��ᰡ �ֳ�
	{
		return false;
	}

	return true;
}

void APot::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
}

void APot::ForwardCookingTable(ACookingTable* Table)
{
	CookingTable = Table;
}

void APot::ForwardAttachToChef()
{
	CookingTable = nullptr;
}

void APot::SetBoil(ACooking* Rice)
{
	if (nullptr == CookingTable)
	{
		return;
	}
	ABurnerTable* BurnerTable =  Cast<ABurnerTable>(CookingTable);
	if (nullptr == BurnerTable) // 1. ���� ���� �ֳ�
	{
		return; // ���� ���� Ingredient�� �ִ� �Լ��̹Ƿ� CanCook �Լ��� üũ���� �ʴ´�.
	}

	AIngredient* RawRice = Cast<AIngredient>(Rice);
	if (nullptr == RawRice) // 2. ��ᰡ ���̳�
	{
		return;
	}
	if (EIngredientState::EIS_BOILABLE != RawRice->GetCurIngredientState()) // 3. Boil �� �� �ְ�, ������ �� �� ���°� �³�
	{
		return;
	}

	// ����ó���� ����� �� �ִ� ���� �� ���̹Ƿ� ������� ���� ������ ���� ���� ���̴�.

	Ingredient = RawRice;
	PotState = EPotState::BOILING;

	bIsBoiling = true;


	// ���̷�Ż �޽ÿ� ���� �ִϸ��̼� ����ؾ���

	return;
}

AIngredient* APot::GetCookedIngredient()
{
	Ingredient->ChangeState(EIngredientState::EIS_BOILED);

	AIngredient* CookedIngredient = Ingredient;
	Ingredient = nullptr;

	return CookedIngredient;
}

