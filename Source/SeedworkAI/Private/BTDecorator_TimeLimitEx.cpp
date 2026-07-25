// Copyright (c) Mistfly Games. All Rights Reserved.

#include "BTDecorator_TimeLimitEx.h"
#include "SeedworkRandom.h"

UBTDecorator_TimeLimitEx::UBTDecorator_TimeLimitEx()
{
    NodeName = "TimeLimit Ex";
    bNotifyActivation = true;
    bNotifyTick = true;
    bTickIntervals = true;

    // time limit always abort current branch
    bAllowAbortLowerPri = false;
    bAllowAbortNone = false;
    FlowAbortMode = EBTFlowAbortMode::Self;
}

#if WITH_EDITOR
FName UBTDecorator_TimeLimitEx::GetNodeIconName() const
{
    return FName("BTEditor.Graph.BTNode.Decorator.TimeLimit.Icon");
}
#endif

void UBTDecorator_TimeLimitEx::OnNodeActivation(FBehaviorTreeSearchData& SearchData)
{
    uint8* RawMemory = SearchData.OwnerComp.GetNodeMemory(this, SearchData.OwnerComp.FindInstanceContainingNode(this));

    check(RawMemory);

    FBTAuxiliaryMemory* DecoratorMemory = GetSpecialNodeMemory<FBTAuxiliaryMemory>(RawMemory);
    DecoratorMemory->NextTickRemainingTime = URandom::Shared()->DoubleInRange(TimeLimitMin, TimeLimitMax);
    DecoratorMemory->AccumulatedDeltaTime = 0.0f;
}

void UBTDecorator_TimeLimitEx::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    OwnerComp.RequestExecution(this);
}
