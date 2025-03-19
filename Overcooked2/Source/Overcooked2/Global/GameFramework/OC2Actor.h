// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Global/Interface/Interactable.h"
#include "OC2Actor.generated.h"

UCLASS()
class OVERCOOKED2_API AOC2Actor : public AActor//, public IInteractable
{
    GENERATED_BODY()

public:
    /** �⺻ ������ */
    AOC2Actor();

public:
    /** OC2Actor �ʱ�ȭ �Լ� */
    virtual void InitOC2Actor();

public:
    /** ��Ƽ���� ���̶���Ʈ ȿ�� ���� */
    UFUNCTION(BlueprintCallable, Reliable, NetMulticast)
    virtual void ApplyMaterialHighlight();

    /** ��Ƽ���� ���̶���Ʈ ȿ�� ���� */
    UFUNCTION(BlueprintCallable, Reliable, NetMulticast)
    virtual void RestoreMaterial();

    /**
     * StaticMeshComponent ��ȯ
     * @return StaticMeshComponent�� ������
     */
    UFUNCTION(BlueprintCallable)
    UStaticMeshComponent* GetStaticMeshComponent()
    {
        return StaticMeshComponent;
    }

    /**
     * ���̶���Ʈ ���� Ȯ��
     * @return ���� ���̶���Ʈ ���� (true: ���̶���Ʈ �����, false: ������)
     */
    UFUNCTION(BlueprintCallable)
    bool IsHighlighted()
    {
        return bIsHighlighted;
    }

    /** Ŭ���̾�Ʈ�� �������� ���� ���� ��û�� ���� �Լ� (RPC) */
    UFUNCTION(BlueprintCallable, Category = "Global")
    void RequestOC2ActorDestroy();

    /** �������� ���͸� �����ϴ� �Լ� (RPC ����) */
    UFUNCTION(Server, Reliable, WithValidation)
    void Server_DestroyOC2Actor();

    /**
     * ��Ʈ��ũ ����ȭ�� ���� Replicated ������Ƽ ���
     * @param OutLifetimeProps ��Ʈ��ũ ����ȭ�� ���� ���
     */
    void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    /** ���� ���� �� ȣ��Ǵ� �Լ� */
    virtual void BeginPlay() override;

    /**
     * �� �����Ӹ��� ȣ��Ǵ� �Լ�
     * @param DeltaTime ������ �� �ð� ����
     */
    virtual void Tick(float DeltaTime) override;

    /** ������ ��Ƽ���� ����Ʈ */
    TArray<UMaterialInterface*> Materials;

    /** ��Ƽ������ DiffuseColorMap ����ġ ����Ʈ */
    TArray<float> DiffuseColorMapWeights;

    /** ���̶���Ʈ ���� ���� */
    bool bIsHighlighted = false;

    /** ������ StaticMeshComponent */
    UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* StaticMeshComponent = nullptr;

    /** ������ SceneComponent */
    UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "Cooking", meta = (AllowPrivateAccess = "true"))
    USceneComponent* SecenComponent = nullptr;
};
