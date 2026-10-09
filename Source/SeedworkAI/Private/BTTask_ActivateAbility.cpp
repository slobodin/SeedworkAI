// Copyright (c) Mistfly Games. All Rights Reserved.

#include "BTTask_ActivateAbility.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"

/*
FIXME: Bugs?

BTTask_ActivateAbility.cpp — this file has the most serious problems


2. OnAbilityEnded is never unbound
It's bound in ExecuteTask (line 46) and the only removal is RemoveAll(this) at the start of the next ExecuteTask.
So after the task succeeds or aborts, the node instance stays subscribed to the ASC.
Concrete failure: task aborts with CancelAbilityOnTaskAbort = false → the ability keeps running → it ends 3 seconds later → HandleAbilityEnded fires and
calls FinishLatentTask(Succeeded) on a node that is no longer executing. That corrupts BT execution state.

3. AbortTask finishes the task as Succeeded while aborting
asc->CancelAbilityHandle(SpecHandle);   // broadcasts OnAbilityEnded synchronously
...
return Super::AbortTask(...);           // returns Aborted
CancelAbilityHandle broadcasts OnAbilityEnded inline, so HandleAbilityEnded runs before AbortTask returns and calls FinishLatentTask(*MyOwnerComp, Succeeded) mid - abort.Unbind before cancelling.

4. Instantly - ending abilities hang the task forever
TryActivateAbility(line 41) can activate and end an ability entirely inside the call — that's the normal path for instant/GameplayAbilitys with no async tasks. OnAbilityEnded has already broadcast by the time you bind at line 46, so the task returns InProgress and never finishes. Bind the delegate and set SpecHandle before TryActivateAbility.

5. HandleAbilityEnded ignores cancellation and deref's MyOwnerComp unchecked
endedData.bWasCancelled is never consulted — a cancelled ability reports Succeeded.And * MyOwnerComp(line 75) has no IsValid guard.

A shape that fixes 1–5:
EBTNodeResult::Type UBTTask_ActivateAbility::ExecuteTask(UBehaviorTreeComponent & ownerComp, uint8 * nodeMemory)
{
    AAIController* controller = ownerComp.GetAIOwner();
    APawn* myPawn = controller ? controller->GetPawn() : nullptr;
    if (!IsValid(myPawn) || !AbilityClass)
    {
        return EBTNodeResult::Failed;
    }



    MyOwnerComp = &ownerComp;
    SpecHandle = spec->Handle;
    bFinished = false;

    asc->OnAbilityEnded.RemoveAll(this);
    asc->OnAbilityEnded.AddUObject(this, &UBTTask_ActivateAbility::HandleAbilityEnded);

    if (!asc->TryActivateAbility(SpecHandle))
    {
        Unbind(asc);
        return EBTNodeResult::Failed;
    }

    // ability may have already completed synchronously inside TryActivateAbility
    return bFinished ? LatentResult : EBTNodeResult::InProgress;
}
with Unbind() called from HandleAbilityEnded, AbortTask(before CancelAbilityHandle), and OnTaskFinished.

*/

UBTTask_ActivateAbility::UBTTask_ActivateAbility()
{
    NodeName = "Activate Ability";

    // IMPORTANT: instantiating to be able to use Delegates
    bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_ActivateAbility::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
    checkf(false, TEXT("Review the above FIXME comments before using this code"));

    APawn* myPawn = ownerComp.GetAIOwner()->GetPawn();

    if (!IsValid(myPawn))
    {
        return EBTNodeResult::Failed;
    }

    auto asc = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(myPawn);
    FGameplayAbilitySpec* spec = asc ? asc->FindAbilitySpecFromClass(AbilityClass) : nullptr;
    if (!spec)
    {
        return EBTNodeResult::Failed;
    }

    MyOwnerComp = &ownerComp;

    bool activated = false;

    if (asc->TryActivateAbility(spec->Handle))
    {
        SpecHandle = spec->Handle;

        asc->OnAbilityEnded.RemoveAll(this);
        asc->OnAbilityEnded.AddUObject(this, &UBTTask_ActivateAbility::HandleAbilityEnded);

        activated = true;
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
