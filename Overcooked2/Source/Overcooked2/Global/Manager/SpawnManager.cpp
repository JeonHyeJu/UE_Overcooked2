// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Manager/SpawnManager.h"
#include "LevelContent/Table/CookingTable.h"
#include "EngineUtils.h"

// Sets default values
ASpawnManager::ASpawnManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();

	// TActorIterator�� ����Ͽ� ���� �� ��� APrepTable ���͸� ��ȸ
	for (TActorIterator<ACookingTable> It(GetWorld()); It; ++It)
	{
		ACookingTable* PrepTableActor = *It;
		if (PrepTableActor->Tags.Contains("Plate"))
		{
			Tables.Add(PrepTableActor);
		}
		GEngine->AddOnScreenDebugMessage(0, 10.0f, FColor::Blue, PrepTableActor->GetName());
	}
	GEngine->AddOnScreenDebugMessage(0, 10.0f, FColor::Blue, FString::Printf(TEXT("My Value is: %d"), Tables.Num()));
}

// Called every frame
void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

