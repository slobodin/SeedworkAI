// Copyright (c) Mistfly Games. All Rights Reserved.

#include "BotCreationComponent.h"
#include "AIController.h"
#include "Engine/World.h"

// HACK to access GenericPlayerInitialization
#define protected public
#include "GameFramework/GameModeBase.h"
#undef protected

#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "SeedworkRandom.h"

namespace
{
    FString CreateBotName(int32 idx)
    {
        return FString::Printf(TEXT("Tinplate_%d"), idx);
    }
}

UBotCreationComponent::UBotCreationComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

#if WITH_SERVER_CODE

void UBotCreationComponent::SpawnOneBot()
{
    int32 idx = URandom::Shared().IntegerInRange(1, 100);

    FActorSpawnParameters spawnInfo;
    spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    spawnInfo.OverrideLevel = GetComponentLevel();
    spawnInfo.ObjectFlags |= RF_Transient;
    spawnInfo.NameMode = FActorSpawnParameters::ESpawnActorNameMode::Requested;
    spawnInfo.Name = *FString::Printf(TEXT("BotController_%d"), idx);
    spawnInfo.CustomPreSpawnInitalization = [](AActor* actor)
    {
        // TODO: custom initialization if required.
        // CastChecked<ANPCAIController>(actor)->BackendPlayerId = botData.PlayerId;
    };

    auto botController = GetWorld()->SpawnActor<AAIController>(BotControllerClass, FVector::ZeroVector, FRotator::ZeroRotator, spawnInfo);

    check(IsValid(botController));

    if (botController->PlayerState != nullptr)
    {
        botController->PlayerState->SetPlayerName(CreateBotName(idx));
    }

    auto gm = GetWorld()->GetAuthGameMode();

    gm->GenericPlayerInitialization(botController);

    // TODO: restart player based on input param.
    gm->RestartPlayer(botController);

    SpawnedBotList.Add(botController);
}

void UBotCreationComponent::RemoveOneBot()
{
    if (SpawnedBotList.Num() > 0)
    {
        const int32 botToRemoveIndex = FMath::RandRange(0, SpawnedBotList.Num() - 1);

        AAIController* botToRemove = SpawnedBotList[botToRemoveIndex];
        SpawnedBotList.RemoveAtSwap(botToRemoveIndex);

        if (botToRemove)
        {
            if (auto controlledPawn = botToRemove->GetPawn())
            {
                controlledPawn->Destroy();
            }

            // Destroy the controller (will cause it to Logout, etc...)
            botToRemove->Destroy();
        }
    }
}

#else

void UBotCreationComponent::SpawnOneBot()
{
    checkNoEntry();
}

void UBotCreationComponent::RemoveOneBot()
{
    checkNoEntry();
}

#endif
