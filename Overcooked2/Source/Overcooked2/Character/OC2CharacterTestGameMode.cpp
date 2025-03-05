// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/OC2CharacterTestGameMode.h"
#include "LevelContent/Cook/Ingredient.h"
#include "Net/UnrealNetwork.h"

void AOC2CharacterTestGameMode::ServerSpawnIngredient_Implementation()
{
    if (HasAuthority()) // ���������� ����
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        FVector SpawnLocation = FVector(0, 0, 100);
        FRotator SpawnRotation = FRotator::ZeroRotator;

        AIngredient* NewIngredient = GetWorld()->SpawnActor<AIngredient>(AIngredient::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
        if (NewIngredient)
        {
            NewIngredient->SetReplicates(true); // ���Ͱ� �����ǵ��� ����
        }
    }
}

bool AOC2CharacterTestGameMode::ServerSpawnIngredient_Validate()
{
    return true;
}