// Copyright (c) Mistfly Games. All Rights Reserved.

#include "AIUtilityLibrary.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/Pawn.h"

namespace
{
    UBlackboardComponent* GetBBComponent(const APawn* pawn)
    {
        if (IsValid(pawn))
        {
            if (auto ctr = pawn->GetController<AAIController>())
            {
                return ctr->GetBlackboardComponent();
            }
        }

        return nullptr;
    }
}

void UAIUtilityLibrary::SetAIValue_Bool(APawn* pawn, FName key, bool value)
{
    if (auto bb = GetBBComponent(pawn))
    {
        bb->SetValueAsBool(key, value);
    }
}

bool UAIUtilityLibrary::GetAIValue_Bool(const APawn* pawn, FName key)
{
    if (auto bb = GetBBComponent(pawn))
    {
        return bb->GetValueAsBool(key);
    }

    return false;
}

void UAIUtilityLibrary::SetAIValue_Int(APawn* pawn, FName key, int32 value)
{
    if (auto bb = GetBBComponent(pawn))
    {
        bb->SetValueAsInt(key, value);
    }
}

void UAIUtilityLibrary::SetAIValue_Enum(APawn* pawn, FName key, uint8 value)
{
    if (auto bb = GetBBComponent(pawn))
    {
        bb->SetValueAsEnum(key, value);
    }
}

int32 UAIUtilityLibrary::GetAIValue_Int(const APawn* pawn, FName key)
{
    if (auto bb = GetBBComponent(pawn))
    {
        return bb->GetValueAsInt(key);
    }

    return 0;
}

void UAIUtilityLibrary::SetAIValue_Float(APawn* pawn, FName key, float value)
{
    if (auto bb = GetBBComponent(pawn))
    {
        bb->SetValueAsFloat(key, value);
    }
}

float UAIUtilityLibrary::GetAIValue_Float(const APawn* pawn, FName key)
{
    if (auto bb = GetBBComponent(pawn))
    {
        return bb->GetValueAsFloat(key);
    }

    return 0.0f;
}

void UAIUtilityLibrary::SetAIValue_Name(APawn* pawn, FName key, FName value)
{
    if (auto bb = GetBBComponent(pawn))
    {
        bb->SetValueAsName(key, value);
    }
}

FName UAIUtilityLibrary::GetAIValue_Name(const APawn* pawn, FName key)
{
    if (auto bb = GetBBComponent(pawn))
    {
        return bb->GetValueAsName(key);
    }

    return NAME_None;
}

void UAIUtilityLibrary::SetAIValue_Vector(APawn* pawn, FName key, FVector value)
{
    if (auto bb = GetBBComponent(pawn))
    {
        bb->SetValueAsVector(key, value);
    }
}

FVector UAIUtilityLibrary::GetAIValue_Vector(const APawn* pawn, FName key)
{
    if (auto bb = GetBBComponent(pawn))
    {
        return bb->GetValueAsVector(key);
    }

    return FVector::ZeroVector;
}

void UAIUtilityLibrary::SetAIValue_Actor(APawn* pawn, FName key, AActor* value)
{
    if (auto bb = GetBBComponent(pawn))
    {
        bb->SetValueAsObject(key, value);
    }
}

AActor* UAIUtilityLibrary::GetAIValue_Actor(const APawn* pawn, FName key)
{
    if (auto bb = GetBBComponent(pawn))
    {
        auto obj = bb->GetValueAsObject(key);
        return IsValid(obj) ? Cast<AActor>(obj) : nullptr;
    }

    return nullptr;
}

void UAIUtilityLibrary::StartBehaviour(APawn* pawn, UBehaviorTree* newBehaviour)
{
    if (!IsValid(pawn))
    {
        ensure(false);
        return;
    }

    unimplemented();

    /*

    if (auto npcConfig = IGameplayEntity::GetNPCConfigFromEntity(pawn))
    {
        if (auto healthComp = IGameplayEntity::GetHealthFromEntity(pawn))
        {
            if ((newBehaviour != nullptr) && !healthComp->IsAlive())
            {
                GAME_WARNING("Trying to set up AI behaviour on a dead pawn: %s. Aborting.", *pawn->GetName());
                return;
            }
        }

        if (pawn->GetController() == nullptr)
        {
            pawn->SpawnDefaultController();
        }

        if (auto controller = Cast<ANPCAIController>(pawn->GetController()))
        {
            npcConfig->SetBehaviorTree(newBehaviour);

            controller->StopAI();
            controller->StartAI();
        }
    }
    */
}

void UAIUtilityLibrary::StartDefaultBehaviour(APawn* pawn)
{
    unimplemented();

    /*if (auto npcConfig = IGameplayEntity::GetNPCConfigFromEntity(pawn))
    {
        StartBehaviour(pawn, npcConfig->GetInitialBehaviorTree());
    }*/
}
