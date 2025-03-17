#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CookingWidget.generated.h"

UCLASS()
class OVERCOOKED2_API UCookingWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    // �Ϸ�� �ֹ� ���� ���� �� ��ȯ
    UFUNCTION(BlueprintCallable, Category = "OC2UI")
    void SetCompleteOrderNum(int num) { CompleteOrderNum = num; }

    UFUNCTION(BlueprintCallable, Category = "OC2UI")
    int GetCompleteOrderNum() { return CompleteOrderNum; }

    // �ֹ� �Ϸ� ó��
    UFUNCTION(BlueprintCallable, Category = "OC2UI")
    void OrderComplete(int Index);

    // ���ο� �ֹ� ����
    UFUNCTION(BlueprintCallable, Category = "OC2UI")
    void CreateNewOrder(struct FOrder& Order);

    // UI ���ε� (�� 5���� �ֹ� ����)
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "OC2UI")
    class UCanvasPanel* Order_0;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "OC2UI")
    class UCanvasPanel* Order_1;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "OC2UI")
    class UCanvasPanel* Order_2;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "OC2UI")
    class UCanvasPanel* Order_3;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "OC2UI")
    class UCanvasPanel* Order_4;

protected:
    virtual void NativeOnInitialized() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

private:
    // �ֹ� ���� ����
    int CompleteOrderNum = 0;
    int NewOrderNum = 0;
    int CurOrderCount = 0;

    float TimeLimit = 30.f;
    float ImageSize = 230.0f;
    float ImageOffset = 10.0f;
    float IngredientArrivePos = 100.f;
    float OpacityOffset = 0.05f;
    float FinalPos = 0.0f;
    float ArrivePos = 0.0f;

    float IngredientTimeElapsed = 0.0f;
    float MoveTimeElapsed = 0.0f;

    FVector2D TargetOffset = FVector2D(50.0f, 0.0f);
    FVector2D IngredientTargetOffset = FVector2D(0.0f, 10.0f);
    FVector2D IShortSize = { 72.0f, 65.f };
    FVector2D ILongSize = { 72.0f, 115.f };

    TArray<class UCanvasPanel*> Orders;
    TArray<float> OrderTime;
    TArray<struct FOrder> CurOrders;

    // Ÿ�̸� �ڵ�
    FTimerHandle OpacityTimerHandle;
    FTimerHandle MoveTimerHandle;
    FTimerHandle IngredientTimerHandle;

    // ���� �Լ�
    void UpdateImageOpacity();
    void UpdateImagePosition();
    void UpdateIngredientImagePosition();
    void UpdateOrderTime(int Index, float DeltaTime);
    void SettingIngredientImages(FOrder& order);
    void MoveNewOrder();

    template <typename T>
    T* FindChildWidget(const FString& name, UCanvasPanel* canvas);

    class UImage* FindChildImage(const FString& name, UCanvasPanel* canvasPanel);
    class UCanvasPanel* FindChildPanel(const FString& name, UCanvasPanel* canvas);
};
