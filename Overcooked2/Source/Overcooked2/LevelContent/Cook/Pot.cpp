// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelContent/Cook/Pot.h"
#include <LevelContent/Cook/Ingredient.h>
#include <LevelContent/Table/BurnerTable.h>
#include <Net/UnrealNetwork.h>
#include "GameFramework/Character.h"
#include <Global/GameMode/OC2GameMode.h>

APot::APot()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	SetReplicateMovement(true);

	CookingType = ECookingType::ECT_POT;

	SoupSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SoupSkeletalMeshComponent"));
	SoupSkeletalMeshComponent->SetupAttachment(StaticMeshComponent);
	SoupSkeletalMeshComponent->SetIsReplicated(true);


	FVector Pos = FVector(249, 1452, 60);
	StaticMeshComponent->SetRelativeLocation(Pos);
}

void APot::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APot, SoupSkeletalMeshComponent);
	DOREPLIFETIME(APot, SoupDynamicMaterial);
	DOREPLIFETIME(APot, NoneMaterial);
	DOREPLIFETIME(APot, PotState);
	//DOREPLIFETIME(APot, PrevPotState);
	DOREPLIFETIME(APot, bIsRiceInPot);
	DOREPLIFETIME(APot, TimeElapsed);
	DOREPLIFETIME(APot, CookingTable);
}

// Table이 SetCookingTable 함수를 호출해주면 여기서 세팅
void APot::ForwardCookingTable(ACookingTable* Table)
{
	CookingTable = Table;
}

// 캐릭터가 냄비를 들어올렸을 때, 호출
void APot::ForwardAttachToChef()
{
	CookingTable = nullptr;
}

void APot::BeginPlay()
{
	ACooking::BeginPlay();

	NoneMaterial = LoadNoneMaterial(); // 여기서 해줘야 클라도  NULL 머티리얼 생성된다.
	SetSoupMaterial();

	ChangeNoneMaterial();
}

UMaterialInstanceDynamic* APot::LoadNoneMaterial()
{
	const FString NoneMaterialName = TEXT("/Game/Resources/LevelResource/Object/Pot/M_NONE");
	UMaterial* NewMaterial = LoadObject<UMaterial>(nullptr, *NoneMaterialName);
	UMaterialInstanceDynamic* NewMaterialInstanceDynamic = UMaterialInstanceDynamic::Create(NewMaterial, this);
	return NewMaterialInstanceDynamic;
}

void APot::SetSoupMaterial_Implementation()
{
	int32 NumSoupMaterials = SoupSkeletalMeshComponent->GetMaterials().Num();
	if (NumSoupMaterials == SoupDynamicMaterial.Num())
	{
		return;
	}
	for (int32 i = 0; i < NumSoupMaterials; i++)
	{
		UMaterialInstanceDynamic* MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(SoupSkeletalMeshComponent->GetMaterial(i), this);
		SoupDynamicMaterial.Add(MaterialInstanceDynamic);
		SoupSkeletalMeshComponent->SetMaterial(i, MaterialInstanceDynamic);
	}
}

void APot::Tick(float DeltaTime)
{
	ACooking::Tick(DeltaTime);

	Cook(DeltaTime);
	SetAction();
}

void APot::Add_Implementation(AIngredient* Ingredient)
{
	if (true == bIsRiceInPot) // 1. 이미 쌀이 들어와있다면 리턴
	{
		return;
	}

	AIngredient* RawRice = Cast<AIngredient>(Ingredient);
	if (nullptr == RawRice) // 2. 지금 들어온 재료가 쌀이냐
	{
		return;
	}
	if (EIngredientState::EIS_BOILABLE != RawRice->GetCurIngredientState()) // 3. Boil 할 수 있고, 조리가 안 된 상태가 맞냐
	{
		return;
	}

	RawRice->RequestOC2ActorDestroy(); // 들어온 재료는 삭제

	bIsRiceInPot = true;
	PotState = EPotState::HEATING;
}

// 조리 시간 타이머 트리거
bool APot::IsBoiling()
{
	if (false == bIsRiceInPot) // 1. 냄비에 쌀이 있냐
	{
		return false;
	}
	if (nullptr == CookingTable)
	{
		return false;
	}
	ABurnerTable* BurnerTable = Cast<ABurnerTable>(CookingTable);
	if (nullptr == BurnerTable) // 2. 버너 위에 있냐
	{
		return false;
	}
	return true;
}

void APot::Cook(float DeltaTime)
{
	if (false == IsBoiling())
	{
		return;
	}

	TimeElapsed += DeltaTime;

	if (EPotState::HEATING == PotState && 4.0f < TimeElapsed)
	{
		PotState = EPotState::BOILING;
	}
	else if (EPotState::BOILING == PotState && 8.0f < TimeElapsed)
	{
		PotState = EPotState::COOKED;
	}
	else if (EPotState::COOKED == PotState && 12.0f < TimeElapsed)
	{
		PotState = EPotState::OVERCOOKED;
	}
}

void APot::SetAction_Implementation()
{
	if (!HasAuthority())
	{
		int a = 0;
	}

	// 상태가 변경되지 않았으면 리턴
	if (PrevPotState == PotState)
	{
		return;
	}
	PrevPotState = PotState;

	switch (PotState)
	{
	case EPotState::IDLE:
	{
		ChangeNoneMaterial();
		break;
	}
	case EPotState::HEATING:
	{
		int32 NumSoupMaterials = SoupSkeletalMeshComponent->GetMaterials().Num();
		for (int32 i = 0; i < NumSoupMaterials; i++)
		{
			SoupSkeletalMeshComponent->SetMaterial(i, SoupDynamicMaterial[i]);
		}
		break;
	}
	case EPotState::BOILING:
		break;
	case EPotState::COOKED:
	{

	}
		break;
	case EPotState::OVERCOOKED:
	{

	}
		break;
	default:
		break;
	}
}

void APot::ChangeNoneMaterial()
{
	int32 NumSoupMaterials = SoupSkeletalMeshComponent->GetMaterials().Num();
	for (int32 i = 0; i < NumSoupMaterials; i++)
	{
		SoupSkeletalMeshComponent->SetMaterial(i, NoneMaterial);
	}
}

void APot::ChangeMaterialColor(FVector4 Color)
{
	int32 NumSoupMaterials = SoupSkeletalMeshComponent->GetMaterials().Num();
	for (int32 i = 1; i < NumSoupMaterials; i++)
	{
		SoupDynamicMaterial[i]->SetVectorParameterValue(FName("Tint"), Color);
		SoupSkeletalMeshComponent->SetMaterial(i, SoupDynamicMaterial[i]);
	}
}

void APot::ResetPot()
{
	PrevPotState = EPotState::MAX;
	PotState = EPotState::IDLE;
	bIsRiceInPot = false;
	TimeElapsed = 0.0f;

	ChangeNoneMaterial();
}

AIngredient* APot::GetRice()
{
	AGameModeBase* GameModeBase =  GetWorld()->GetAuthGameMode();
	if (nullptr == GameModeBase)
	{
		UE_LOG(LogTemp, Warning, TEXT("nullptr == GameModeBase"));
		return nullptr;
	}

	AOC2GameMode* GameMode = Cast<AOC2GameMode>(GameModeBase);
	if (nullptr == GameMode)
	{
		UE_LOG(LogTemp, Warning, TEXT("nullptr == GameMode"));
		return nullptr;
	}

	AIngredient* Rice = GameMode->SpawnIngredientActor(EIngredientType::EIT_RICE);
	Rice->ChangeState(EIngredientState::EIS_BOILED);

	ResetPot();

	return Rice;
}

