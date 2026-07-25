// Copyright (c) Mistfly Games. All Rights Reserved.

#include "BTTask_ActivateAbility.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"

UBTTask_ActivateAbility::UBTTask_ActivateAbility()
{
    NodeName = "Activate Ability";

    // IMPORTANT: instantiating to be able to use Delegates
    bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_ActivateAbility::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
    APawn* myPawn = ownerComp.GetAIOwner()->GetPawn();

    if (!IsValid(myPawn))
    {
        return EBTNodeResult::Failed;
    }

    auto asc = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(myPawn);

    if (!asc)
    {
        return EBTNodeResult::Failed;
    }

    MyOwnerComp = &ownerComp;

    bool activated = false;

    if (auto spec = asc->FindAbilitySpecFromClass(AbilityClass))
    {
        if (asc->TryActivateAbility(spec->Handle))
        {
            SpecHandle = spec->Handle;

            asc->OnAbilityEnded.RemoveAll(this);
            asc->OnAbilityEnded.AddUObject(this, &UBTTask_ActivateAbility::HandleAbilityEnded);

            activated = true;
        }
    }

    return activated ? EBTNodeResult::InProgress : EBTNodeResult::Failed;
}

EBTNodeResult::Type UBTTask_ActivateAbility::AbortTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
    if (CancelAbilityOnTaskAbort)
    {
        if (auto myPawn = ownerComp.GetAIOwner()->GetPawn())
        {
            if (auto asc = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(myPawn))
            {
                asc->CancelAbilityHandle(SpecHandle);
            }
        }
    }

    return Super::AbortTask(ownerComp, nodeMemory);
}

void UBTTask_ActivateAbility::HandleAbilityEnded(const FAbilityEndedData& endedData)
{
    if (SpecHandle.IsValid() && (endedData.AbilitySpecHandle == SpecHandle))
    {
        FinishLatentTask(*MyOwnerComp, EBTNodeResult::Succeeded);
    }
}
