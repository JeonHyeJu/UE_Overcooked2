// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelContent/Cook/Pot.h"
#include <LevelContent/Cook/Ingredient.h>
#include <LevelContent/Table/BurnerTable.h>
#include <Net/UnrealNetwork.h>

APot::APot()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	SetReplicateMovement(true);

	CookingType = ECookingType::ECT_POT;

	SoupSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SoupSkeletalMeshComponent"));
	SoupSkeletalMeshComponent->SetupAttachment(StaticMeshComponent);
	SoupSkeletalMeshComponent->SetIsReplicated(true);

	UMaterialInstanceDynamic* MaterialInstanceDynamic = Cast<UMaterialInstanceDynamic>(StaticMeshComponent->GetMaterial(0));

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
	ChangeState();
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

void APot::ChangeState()
{
	if (true)
	{

	}

	switch (PotState)
	{
	case EPotState::IDLE:

		break;
	case EPotState::HEATING:
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

void APot::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(APot, SoupSkeletalMeshComponent);
	DOREPLIFETIME(APot, PotState);
	DOREPLIFETIME(APot, PrevPotState);
	DOREPLIFETIME(APot, bIsRiceInPot);
	DOREPLIFETIME(APot, CookingTable);
	DOREPLIFETIME(APot, bIsBoiling);
}

void APot::ForwardCookingTable(ACookingTable* Table)
{
	CookingTable = Table;
}

void APot::ForwardAttachToChef()
{
	CookingTable = nullptr;
}

void APot::Add_Implementation(AIngredient* Ingredient)
{
	if (true == bIsRiceInPot) // 1. �̹� ���� �����ִٸ� ����
	{
		return;
	}

	AIngredient* RawRice = Cast<AIngredient>(Ingredient);
	if (nullptr == RawRice) // 2. ���� ���� ��ᰡ ���̳�
	{
		return;
	}
	if (EIngredientState::EIS_BOILABLE != RawRice->GetCurIngredientState()) // 3. Boil �� �� �ְ�, ������ �� �� ���°� �³�
	{
		return;
	}

	bIsRiceInPot =  true;

	RawRice->RequestOC2ActorDestroy(); // ���� ���� ����
	
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

	// ����ó���� ����� �� �ִ� ���� �� ���̹Ƿ� ������� ���� ������ ���� ���� ���̴�.


	PotState = EPotState::BOILING;
	bIsBoiling = true;


	// ���̷�Ż �޽ÿ� ���� �ִϸ��̼� ����ؾ���

	return;
}

AIngredient* APot::GetCookedIngredient()
{
	return nullptr;
}

