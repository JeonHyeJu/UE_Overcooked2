// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/GameFramework/OC2Actor.h"
#include "Net/UnrealNetwork.h"

AOC2Actor::AOC2Actor()
{
	PrimaryActorTick.bCanEverTick = true;

	SecenComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SecenComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;
	
	//StaticMeshComponent->SetupAttachment(RootComponent);
}

void AOC2Actor::InitOC2Actor()
{
}

void AOC2Actor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AOC2Actor, SecenComponent);
	DOREPLIFETIME(AOC2Actor, StaticMeshComponent);
}

void AOC2Actor::BeginPlay()
{
	Super::BeginPlay();

}

void AOC2Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOC2Actor::ApplyMaterialHighlight()
{
	if (nullptr == StaticMeshComponent)
	{
		return;
	}

	float HighlightValue = 5.0f;
	UMeshComponent* Mesh = nullptr;
	if (nullptr == (Mesh = FindComponentByClass<USkeletalMeshComponent>()))
	{
		Mesh = StaticMeshComponent;
	}

	for (int i = 0; i < Mesh->GetNumMaterials(); i++)
	{
		if (Mesh->GetMaterials().IsValidIndex(i) && Mesh->GetMaterials()[i] != nullptr)
		{
			UMaterialInstanceDynamic* ExistingDynamicMaterial = Cast<UMaterialInstanceDynamic>(Mesh->GetMaterials()[i]);
			if (ExistingDynamicMaterial)
			{
				// �̹� �����ϴ� ���̳��� ��Ƽ������ ������ ���� ����
				Mesh->GetMaterial(0)->GetScalarParameterValue(FName("DiffuseColorMapWeight"), DiffuseColorMapWeight);
				ExistingDynamicMaterial->SetScalarParameterValue(FName("DiffuseColorMapWeight"), HighlightValue);
				continue;
			}
		}

		// 1. �޽��� ��Ƽ������ ��� �����´�.
		UMaterialInterface* Material = Mesh->GetMaterial(i);
		if (nullptr != Material)
		{
			// 2. ���� ��Ƽ���� �ν��Ͻ��� �����Ѵ�.
			// ���� ��Ƽ������ ����ƽ�̶� ������ �� ����.
			UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);

			if (nullptr != DynamicMaterial)
			{
				// 3. ���� ��Ƽ������ ���� �����ϰ�
				Material->GetScalarParameterValue(FName("DiffuseColorMapWeight"), DiffuseColorMapWeight);
				//Materials.Add(Material);

				// 4. ���̳��� ��Ƽ����� ��ü�Ѵ�.
				DynamicMaterial->SetScalarParameterValue(FName("DiffuseColorMapWeight"), HighlightValue);
				Mesh->SetMaterial(i, DynamicMaterial);
			}
		}
	}
	bIsHighlighted = true;
}

void AOC2Actor::RestoreMaterial()
{
	UMeshComponent* Mesh = nullptr;
	if (nullptr == (Mesh = GetComponentByClass<USkeletalMeshComponent>()))
	{
		Mesh = StaticMeshComponent;
	}

	if (Mesh != nullptr)
	{
		for (int i = 0; i < Mesh->GetNumMaterials(); i++)
		{
			if (Mesh->GetMaterials().IsValidIndex(i) && Mesh->GetMaterials()[i] != nullptr)
			{
				UMaterialInstanceDynamic* ExistingDynamicMaterial = Cast<UMaterialInstanceDynamic>(Mesh->GetMaterials()[i]);
				if (ExistingDynamicMaterial)
				{
					// �̹� �����ϴ� ���̳��� ��Ƽ������ ������ ���� ����
					ExistingDynamicMaterial->SetScalarParameterValue(FName("DiffuseColorMapWeight"), DiffuseColorMapWeight);
					continue;
				}
			}

			UMaterialInterface* Material = Materials[i];
			if (nullptr != Material)
			{
				UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
				if (nullptr != DynamicMaterial)
				{
					DynamicMaterial->SetScalarParameterValue(FName("DiffuseColorMapWeight"), DiffuseColorMapWeight);
					Mesh->SetMaterial(i, DynamicMaterial);
				}
			}
		}
	}
	

	// 2. �����ص� ��Ƽ������ �ʱ�ȭ
	Materials.Empty();
	bIsHighlighted = false;
}