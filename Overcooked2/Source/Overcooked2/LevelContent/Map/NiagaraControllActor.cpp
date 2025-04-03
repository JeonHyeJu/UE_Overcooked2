// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelContent/Map/NiagaraControllActor.h"
#include "NiagaraControllActor.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
ANiagaraControllActor::ANiagaraControllActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment(RootComponent);
	NiagaraComponent->SetAutoActivate(false); // �⺻ �ڵ� ������

	TimeEventComponent = CreateDefaultSubobject<UTimeEventComponent>(TEXT("TimeEventComponent"));
	
}

void ANiagaraControllActor::SetActivate(bool Value)
{
	if (nullptr != NiagaraComponent->GetAsset())
	{
		if (true == Value)
		{
			NiagaraComponent->Activate(true);
		}
		else
		{
			NiagaraComponent->Deactivate();

		}
	}
}

// Called when the game starts or when spawned
void ANiagaraControllActor::BeginPlay()
{
	Super::BeginPlay();

	if (nullptr != NiagaraComponent)
	{
		if (nullptr != NiagaraSystem)
		{
			NiagaraComponent->SetAsset(NiagaraSystem);
		}
	}

	TimeEventComponent->AddEndEvent(InitDelayTime, [this]()
		{
			SetActivate(true);
			bIsFirstCalled = true;
		});
}

// Called every frame
void ANiagaraControllActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (true == bUseCycle)
	{
		if (false == bLoopStart) // ���� ���� ȣ�� ���� 
		{
			if (true == bIsFirstCalled)
			{
				bIsFirstCalled = false;

				TimeEventComponent->AddEndEvent(RenderDuration, [this]() // n�� �� �ٽ� ��.
					{
						SetActivate(false); // ������ ����
						bLoopStart = true;
					});
			}
			return;
		}
	}

	UpdateLoopCycle(DeltaTime);
}

void ANiagaraControllActor::UpdateLoopCycle(float DeltaTime)
{
	if (true == bUseCycle)
	{
		TimeElpased += DeltaTime;
		if (TimeElpased >= CycleCooldown)
		{
			if (false == bCanCalled) // ���� �� �� �� ���� �Ʒ� �ڵ� ����
			{
				SetActivate(true); // ������

				bCanCalled = true;
				TimeEventComponent->AddEndEvent(RenderDuration, [this]() // n�� �� �ٽ� ��.
					{
						SetActivate(false); // ������ ����
						bCanCalled = false; // ��Ÿ�� �ʱ�ȭ
						TimeElpased = 0.0f;
					});
			}
		}
	}
}

