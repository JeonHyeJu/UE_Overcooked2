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
	TArray<UMeshComponent*> MeshComponents;
	GetComponents<UMeshComponent>(MeshComponents);

	if (true == MeshComponents.IsEmpty())
	{
		return;
	}

	DiffuseColorMapWeights.SetNumZeroed(10);
	float HighlightValue = 100.0f;
	int Count = 0;

	for (UMeshComponent* Mesh : MeshComponents)
	{
		if (nullptr == Mesh)
		{
			continue;
		}

		for (int i = 0; i < Mesh->GetNumMaterials(); i++)
		{
			// ���̳��� ��Ƽ����� ��ü�� ������ ���
			if (true == Mesh->GetMaterials().IsValidIndex(i) && nullptr != Mesh->GetMaterials()[i])
			{
				UMaterialInstanceDynamic* ExistingDynamicMaterial = Cast<UMaterialInstanceDynamic>(Mesh->GetMaterials()[i]);
				if (nullptr != ExistingDynamicMaterial)
				{
					Mesh->GetMaterials()[i]->GetScalarParameterValue(FName("DiffuseAdd"), DiffuseColorMapWeights[Count]);
					ExistingDynamicMaterial->SetScalarParameterValue(FName("DiffuseAdd"), HighlightValue);
					Mesh->SetMaterial(i, ExistingDynamicMaterial);
					float Result = 0.0f;
					Mesh->GetMaterials()[i]->GetScalarParameterValue(FName("DiffuseAdd"), Result);
					Result;
					++Count;
					continue;
				}
			}
			
			// ���� ���̶���Ʈ
			UMaterialInterface* Material = Mesh->GetMaterials()[i];
			if (nullptr != Material)
			{
				UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
				if (nullptr != DynamicMaterial)
				{
					Mesh->GetMaterials()[i]->GetScalarParameterValue(FName("DiffuseAdd"), DiffuseColorMapWeights[Count]);
					DynamicMaterial->SetScalarParameterValue(FName("DiffuseAdd"), HighlightValue);
					Mesh->SetMaterial(i, DynamicMaterial);
					++Count;
				}
			}
		}
	}

	//for (int i = 0; i < Mesh->GetNumMaterials(); i++)
	//{
	//	if (Mesh->GetMaterials().IsValidIndex(i) && Mesh->GetMaterials()[i] != nullptr)
	//	{
	//		UMaterialInstanceDynamic* ExistingDynamicMaterial = Cast<UMaterialInstanceDynamic>(Mesh->GetMaterials()[i]);
	//		if (ExistingDynamicMaterial)
	//		{
	//			// �̹� �����ϴ� ���̳��� ��Ƽ������ ������ ���� ����
	//			Mesh->GetMaterials()[i]->GetScalarParameterValue(FName("DiffuseColorMapWeight"), DiffuseColorMapWeight);
	//			ExistingDynamicMaterial->SetScalarParameterValue(FName("DiffuseColorMapWeight"), HighlightValue);
	//			continue;
	//		}
	//	}

	//	// 1. �޽��� ��Ƽ������ ��� �����´�.
	//	UMaterialInterface* Material = Mesh->GetMaterial(i);
	//	if (nullptr != Material)
	//	{
	//		// 2. ���� ��Ƽ���� �ν��Ͻ��� �����Ѵ�.
	//		// ���� ��Ƽ������ ����ƽ�̶� ������ �� ����.
	//		UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);

	//		if (nullptr != DynamicMaterial)
	//		{
	//			// 3. ���� ��Ƽ������ ���� �����ϰ�
	//			Material->GetScalarParameterValue(FName("DiffuseColorMapWeight"), DiffuseColorMapWeight);
	//			//Materials.Add(Material);

	//			// 4. ���̳��� ��Ƽ����� ��ü�Ѵ�.
	//			DynamicMaterial->SetScalarParameterValue(FName("DiffuseColorMapWeight"), HighlightValue);
	//			Mesh->SetMaterial(i, DynamicMaterial);
	//		}
	//	}
	//}
	bIsHighlighted = true;
}

void AOC2Actor::RestoreMaterial()
{
	TArray<UMeshComponent*> MeshComponents;
	GetComponents<UMeshComponent>(MeshComponents);
	if (true == MeshComponents.IsEmpty())
	{
		return;
	}

	int Count = 0;
	for (UMeshComponent* Mesh : MeshComponents)
	{
		if (nullptr == Mesh)
		{
			continue;
		}

		for (int i = 0; i < Mesh->GetNumMaterials(); i++)
		{
			if (true == Mesh->GetMaterials().IsValidIndex(i) && nullptr != Mesh->GetMaterials()[i])
			{
				UMaterialInstanceDynamic* ExistingDynamicMaterial = Cast<UMaterialInstanceDynamic>(Mesh->GetMaterials()[i]);
				if (nullptr != ExistingDynamicMaterial)
				{
					ExistingDynamicMaterial->SetScalarParameterValue(FName("DiffuseAdd"), DiffuseColorMapWeights[Count]);
					Mesh->SetMaterial(i, ExistingDynamicMaterial);
					++Count;
				}
			}
		}
	}

	// 2. �����ص� ��Ƽ������ �ʱ�ȭ
	Materials.Empty();
	DiffuseColorMapWeights.Empty();
	bIsHighlighted = false;
}