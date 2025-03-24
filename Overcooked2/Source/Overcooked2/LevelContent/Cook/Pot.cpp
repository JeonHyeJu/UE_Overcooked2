// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelContent/Cook/Pot.h"
#include <LevelContent/Cook/Ingredient.h>
#include <LevelContent/Table/BurnerTable.h>
#include <Net/UnrealNetwork.h>
#include "GameFramework/Character.h"
#include <Global/GameMode/OC2GameMode.h>
#include "Components/BillboardComponent.h"  

APot::APot()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	SetReplicateMovement(true);

	CookingType = ECookingType::ECT_POT;

	SoupSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SoupSkeletalMeshComponent"));
	SoupSkeletalMeshComponent->SetupAttachment(StaticMeshComponent);
	SoupSkeletalMeshComponent->SetIsReplicated(true);

	InitTexture();

	FVector Pos = FVector(249, 1452, 60);
	StaticMeshComponent->SetRelativeLocation(Pos);
}


void APot::InitTexture()
{
	TextureBillboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("TextureBillboard"));
	TextureBillboard->bHiddenInGame = false;
	TextureBillboard->bIsScreenSizeScaled = true;
	TextureBillboard->bReceivesDecals = false;

	FVector Scale(0.8f, 0.8f, 0.8f);
	TextureBillboard->SetRelativeScale3D(Scale);

	TextureBillboard->SetUsingAbsoluteRotation(true);
	TextureBillboard->SetUsingAbsoluteLocation(true);
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

// Table�� SetCookingTable �Լ��� ȣ�����ָ� ���⼭ ����
void APot::ForwardCookingTable(ACookingTable* Table)
{
	CookingTable = Table;
}

// ĳ���Ͱ� ���� ���÷��� ��, ȣ��
void APot::ForwardAttachToChef()
{
	CookingTable = nullptr;
}

void APot::BeginPlay()
{
	ACooking::BeginPlay();

	NoneMaterial = LoadNoneMaterial(); // ���⼭ ����� Ŭ��  NULL ��Ƽ���� �����ȴ�.
	SetSoupMaterial();
	ChangeNoneMaterial();

	SetWarningTexture();
}

UMaterialInstanceDynamic* APot::LoadNoneMaterial()
{	
	const FString NoneMaterialName = TEXT("/Game/Resources/LevelResource/CookObject/Object/Pot/Soup/M_NONE");
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

void APot::SetWarningTexture()
{
	const FString WarningTextureName = TEXT("/Game/Resources/LevelResource/CookObject/Object/FireExtinguisher/DangerLight/BurnWarning");
	UTexture2D* NewTexture = LoadObject<UTexture2D>(nullptr, *WarningTextureName);
	if (nullptr != NewTexture)
	{
		TextureBillboard->SetSprite(NewTexture);
	}
}

void APot::Tick(float DeltaTime)
{
	ACooking::Tick(DeltaTime);

	Cook(DeltaTime);
	SetAction();

	SetWarnigTextureOffset();
}

void APot::SetWarnigTextureOffset()
{
	if (nullptr != TextureBillboard)
	{
		FRotator FixedRotation = FRotator(0, 0, 0);
		TextureBillboard->SetWorldRotation(FixedRotation);

		FVector OffsetPos = FVector(0, -100, 50);
		TextureBillboard->SetWorldLocation(GetActorLocation() + OffsetPos);
	}
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

	RawRice->RequestOC2ActorDestroy(); // ���� ���� ����

	bIsRiceInPot = true;
	PotState = EPotState::HEATING;
}

// ���� �ð� Ÿ�̸� Ʈ����
bool APot::IsBoiling()
{
	if (false == bIsRiceInPot) // 1. ���� ���� �ֳ�
	{
		return false;
	}
	if (nullptr == CookingTable)
	{
		return false;
	}
	ABurnerTable* BurnerTable = Cast<ABurnerTable>(CookingTable);
	if (nullptr == BurnerTable) // 2. ���� ���� �ֳ�
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

	// ���°� ������� �ʾ����� ����
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

