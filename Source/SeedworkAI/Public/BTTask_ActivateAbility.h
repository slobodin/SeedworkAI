// Copyright (c) Mistfly Games. All Rights Reserved.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "GameplayAbilitySpecHandle.h"
#include "BTTask_ActivateAbility.generated.h"

class UGameplayAbility;
struct FAbilityEndedData;

/**
 * NOTE: Activates ability and waits till its ended.
 * INSTANTIATED Node
 */
UCLASS()
class SEEDWORKAI_API UBTTask_ActivateAbility : public UBTTaskNode
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    TSubclassOf<UGameplayAbility> AbilityClass;

    UPROPERTY(EditAnywhere)
    bool CancelAbilityOnTaskAbort = false;

    UBTTask_ActivateAbility();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory) override;
    virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory) override;

private:
    UPROPERTY()
    TObjectPtr<UBehaviorTreeComponent> MyOwnerComp = nullptr;

    FGameplayAbilitySpecHandle SpecHandle;

    void HandleAbilityEnded(const FAbilityEndedData& endedData);
};
