// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WorldMap/UI/WorldMapUserWidget.h"
#include "Components/Image.h"

void UWorldMapUserWidget::NativeConstruct()
{
    Super::NativeConstruct();


    if (TransitionImg != nullptr)
    {
        TransitionMaterial = TransitionImg->GetDynamicMaterial();

        if (!TransitionMaterial)
        {
            TransitionMaterial = TransitionImg->GetDynamicMaterial();
        }
    }
    TransitionImg->SetVisibility(ESlateVisibility::Hidden);

}


void UWorldMapUserWidget::PlayZoomInAnimation()
{
    if (!TransitionMaterial) return;
    TransitionImg->SetVisibility(ESlateVisibility::Visible);

    float AnimationDuration = 20.0f; // ��ü �ִϸ��̼� ���� (1��)
    float TimeStep = 0.01f; // 0.01��(10ms)���� ������Ʈ
    float CurrentTime = 0.0f; // ���� �ִϸ��̼� ���� �ð�

    GetWorld()->GetTimerManager().ClearTimer(AnimationTimer);

    GetWorld()->GetTimerManager().SetTimer(AnimationTimer, [this, AnimationDuration, TimeStep, CurrentTime]() mutable
        {
            if (CurrentTime >= AnimationDuration)
            {
                GetWorld()->GetTimerManager().ClearTimer(AnimationTimer);
            }

            float Value1 = CurrentTime; // �ִϸ��̼� ���� ���� (0 ~ 1)
            float Value2 = (Value1 - 1.0f) / 2.0f; // ���� ����

            TransitionMaterial->SetScalarParameterValue(TEXT("Value1"), Value1);
            TransitionMaterial->SetScalarParameterValue(TEXT("Value2"), Value2);

            if (CurrentTime < 5.0f)
            {
                CurrentTime += TimeStep * 20.0f;
            }
            else
            {
                CurrentTime += TimeStep * 40.0f; // �ð� ������Ʈ
            }


        }, TimeStep, true);
}