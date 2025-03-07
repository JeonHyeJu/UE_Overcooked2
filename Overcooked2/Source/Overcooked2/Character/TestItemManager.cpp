// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TestItemManager.h"
#include "Character/OC2CharacterTestObject.h"

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
	AOC2CharacterTestObject* NewIngredient = GetWorld()->SpawnActorDeferred<AOC2CharacterTestObject>(AOC2CharacterTestObject::StaticClass(), Trans);

	// 2. �޽ø� ã�Ƽ�
	NewIngredient->SetIngredient(Type);

	Trans.SetLocation(FVector(100.0f, 100.0f, 0.0f));
	NewIngredient->FinishSpawning(Trans);

	return NewIngredient;

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

