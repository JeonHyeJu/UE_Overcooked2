// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelContent/Cook/Pot.h"
#include <LevelContent/Cook/Ingredient.h>

APot::APot()
{
	SoupSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SoupSkeletalMeshComponent"));
	SoupSkeletalMeshComponent->SetupAttachment(StaticMeshComponent);
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
	if (false == bIsOnStove) // 1. ���������� ���� �ֳ�
	{
		return false;
	}

	if (nullptr == Ingredient) // 2. ��ᰡ �ֳ�
	{
		return false;
	}

	return true;
}

void APot::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
}

bool APot::SetBoil(ACooking* Rice)
{
	if (false == bIsOnStove) // 1. ���������� ���� �ֳ�
	{
		return false; // ���� ���� Ingredient�� �ִ� �Լ��̹Ƿ� CanCook �Լ��� üũ���� �ʴ´�.
	}

	AIngredient* RawRice = Cast<AIngredient>(Rice);
	if (nullptr == RawRice) // 2. ��ᰡ ���̳�
	{
		return false;
	}
	if (EIngredientState::EIS_BOILABLE != RawRice->GetCurIngredientState()) // 3. Boil �� �� �ְ�, ������ �� �� ���°� �³�
	{
		return false;
	}

	// ����ó���� ����� �� �ִ� ���� �� ���̹Ƿ� ������� ���� ������ ���� ���� ���̴�.

	Ingredient = RawRice;
	PotState = EPotState::BOILING;


	// ���̷�Ż �޽ÿ� ���� �ִϸ��̼� ����ؾ���

	return true;
}

AIngredient* APot::GetCookedIngredient()
{
	Ingredient->ChangeState(EIngredientState::EIS_BOILED);

	AIngredient* CookedIngredient = Ingredient;
	Ingredient = nullptr;

	return CookedIngredient;
}

