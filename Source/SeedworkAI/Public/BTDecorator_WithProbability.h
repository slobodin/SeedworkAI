// Copyright (c) Mistfly Games. All Rights Reserved.

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_WithProbability.generated.h"

/**
 * Passes execution with certain probability.
 */
UCLASS()
class SEEDWORKAI_API UBTDecorator_WithProbability : public UBTDecorator
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    double Probability = 0.5;

    UBTDecorator_WithProbability();

protected:
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory) const override;

    virtual FString GetStaticDescription() const override;
};
