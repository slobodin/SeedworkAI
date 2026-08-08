// Copyright (c) Mistfly Games. All Rights Reserved.

#include "BTDecorator_WithProbability.h"
#include "SeedworkRandom.h"

UBTDecorator_WithProbability::UBTDecorator_WithProbability()
{
    NodeName = "With Probability";

    bAllowAbortNone = false;
    bAllowAbortLowerPri = false;
    bAllowAbortChildNodes = false;
}

bool UBTDecorator_WithProbability::CalculateRawConditionValue(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory) const
{
    return URandom::Shared().BoolWithWeight(Probability);
}

FString UBTDecorator_WithProbability::GetStaticDescription() const
{
    return FString::Printf(TEXT("%s: %.0f%%"), *Super::GetStaticDescription(), Probability * 100.0);
}
