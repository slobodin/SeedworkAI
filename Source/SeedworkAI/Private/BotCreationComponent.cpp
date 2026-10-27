// Copyright (c) Mistfly Games. All Rights Reserved.

#include "BotCreationComponent.h"
#include "AIController.h"
#include "Engine/World.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Random.h"

namespace
{
    // Bots must go through GenericPlayerInitialization but the function is protected, need to access it.
    struct FGameModeAccess : AGameModeBase
    {
        using AGameModeBase::GenericPlayerInitialization;
    };

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

AAIController* UBotCreationComponent::SpawnOneBot()
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

    (gm->*&FGameModeAccess::GenericPlayerInitialization)(botController);

    // TODO: restart player based on input param.
    gm->RestartPlayer(botController);

    SpawnedBotList.Add(botController);
    return botController;
}

void UBotCreationComponent::RemoveOneBot()
{
    if (SpawnedBotList.Num() > 0)
    {
        const int32 botToRemoveIndex = FMath::RandRange(0, SpawnedBotList.Num() - 1);
        RemoveBot(SpawnedBotList[botToRemoveIndex]);
    }
}

void UBotCreationComponent::RemoveBot(AAIController* bot)
{
    if (SpawnedBotList.RemoveSwap(bot) == 0 || !bot)
    {
        return;
    }

    if (auto controlledPawn = bot->GetPawn())
    {
        controlledPawn->Destroy();
    }

    // Destroy the controller (will cause it to Logout, etc...)
    bot->Destroy();
}

#else

AAIController* UBotCreationComponent::SpawnOneBot()
{
    checkNoEntry();
    return nullptr;
}

void UBotCreationComponent::RemoveOneBot()
{
    checkNoEntry();
}

void UBotCreationComponent::RemoveBot(AAIController* bot)
{
    checkNoEntry();
}

#endif
