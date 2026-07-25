// Copyright (c) Mistfly Games. All Rights Reserved.

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_TimeLimitEx.generated.h"

UCLASS(HideCategories = (Condition))
class SEEDWORKAI_API UBTDecorator_TimeLimitEx : public UBTDecorator
{
    GENERATED_BODY()

public:
    UBTDecorator_TimeLimitEx();

    UPROPERTY(EditAnywhere)
    double TimeLimitMin = 2.0;

    UPROPERTY(EditAnywhere)
    double TimeLimitMax = 5.0;

#if WITH_EDITOR
    virtual FName GetNodeIconName() const override;
#endif // WITH_EDITOR

protected:
    virtual void OnNodeActivation(FBehaviorTreeSearchData& SearchData) override;
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
