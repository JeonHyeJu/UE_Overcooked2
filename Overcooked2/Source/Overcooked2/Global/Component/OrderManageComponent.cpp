// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Component/OrderManageComponent.h"

#include "UI/Cooking/CookingHUD.h"
#include "UI/Cooking/UI/CookingWidget.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UOrderManageComponent::UOrderManageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOrderManageComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UOrderManageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UOrderManageComponent::Multicast_CreateNewOrder_Implementation(FOrder Order)
{
	// ��� Ŭ���̾�Ʈ���� �����
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		ACookingHUD* CookingHUD = Cast<ACookingHUD>(PlayerController->GetHUD());
		if (CookingHUD && CookingHUD->CookWidget)
		{
			CookingHUD->CookWidget->CreateNewOrder(Order);
		}
	}
}
