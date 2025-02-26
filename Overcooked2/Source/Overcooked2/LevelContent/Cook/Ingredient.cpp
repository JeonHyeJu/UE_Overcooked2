// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelContent/Cook/Ingredient.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AIngredient::AIngredient()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent; // ���� �����ָ� nullptr ���ͼ� ����

	// Spawn�Ǵ� �༮�� �⺻ ũ�⸦ ��������� �Ѵٸ�?
	//SetActorScale3D(FVector(100.0f, 100.0f, 100.0f));
}

// ������ ���̺��� ������ �޽ø� ã��, ����� ���¸� �ʱ�ȭ�ϴ� �Լ�
void AIngredient::Init(FName Name)
{
	//UOC2GameInstance* GameInst = Cast<UOC2GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	// 1. ������ ���̺��� �����´�.
	UDataTable* IngredientDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Blueprints/Global/Data/DT_IngredientDataTable.DT_IngredientDataTable"));

	if (nullptr == IngredientDataTable)
	{
		int a = 0;
	}
	
	// 2. �� �̸�(Fish)�� �������� ������ ��("����", �޽ð��, State)�� �����´�.
	FIngredientDataRow* IngredientData = IngredientDataTable->FindRow<FIngredientDataRow>(Name, TEXT(""));
	if (nullptr == IngredientData)
	{
		int a = 0;
	}

	//DataTable = UGlobalDataTable::GetActorClass(Name);
	//DataTable = 
	//StaticMeshComponent->SetStaticMesh(DataTable.BaseMesh);

	// 3. ������ ������ �� ���� �־��ش�.
	StaticMeshComponent->SetStaticMesh(IngredientData->BaseMesh);
	IngredientType = IngredientData->IngredientType;
	CurIngredientState = IngredientData->StateRows[0].PrevIngredientState; // �̰� �³�???
}

const FIngredientCookDataRow& AIngredient::CheckState(EIngredientState State)
{
	const FIngredientCookDataRow* Result = nullptr;

	for (size_t i = 0; i < DataTable.StateRows.Num(); i++)
	{
		if (DataTable.StateRows[i].IngredientState == State)
		{
			Result = &DataTable.StateRows[i];
			break;
		}
	}

	return *Result;
}

void AIngredient::ChageState(EIngredientState State)
{
	const FIngredientCookDataRow* Data = &CheckState(State);

	if (nullptr == Data)
	{
		return;
	}

	CurIngredientState = State;
	StaticMeshComponent->SetStaticMesh(Data->CookMesh);
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

