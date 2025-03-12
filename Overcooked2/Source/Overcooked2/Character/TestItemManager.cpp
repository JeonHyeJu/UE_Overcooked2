// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TestItemManager.h"
#include "Character/OC2CharacterTestObject.h"
#include "Global/OC2Global.h"

// Sets default values for this component's properties
UTestItemManager::UTestItemManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTestItemManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

AActor* UTestItemManager::CreateItem(EIngredientType Type)
{
	FTransform Trans;

	return UOC2Global::SpawnIngredientActor(GetWorld(),Type);

	//ItemActor->SetItemDataKey(_ItemName);
	//// ���۵带 �ϸ� �ظ��ϸ� �̰� ȣ�����ִ°��� �����ϴ�.
	//// ���������� ������ ������ ���忡 ����� ���Խ�Ű�� �Լ��Դϴ�.
	//ItemActor->FinishSpawning(Trans);

	// �ȵǴ� �����
	// NetMultiCast �Լ��� �Ἥ 
	// ItemActor->DataSetting();


	//return ItemActor;
}


// Called every frame
void UTestItemManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

