// Copyright (c) Mistfly Games. All Rights Reserved.

#include "BotCheatManagerExtension.h"
#include "BotCreationComponent.h"
#include "Engine/World.h"
#include "GameFramework/CheatManagerDefines.h"
#include "GameFramework/GameModeBase.h"

UBotCheatManagerExtension::UBotCheatManagerExtension()
{
#if WITH_SERVER_CODE && UE_WITH_CHEAT_MANAGER
    if (HasAnyFlags(RF_ClassDefaultObject))
    {
        UCheatManager::RegisterForOnCheatManagerCreated(FOnCheatManagerCreated::FDelegate::CreateLambda(
            [](UCheatManager* cm)
            {
                cm->AddCheatManagerExtension(NewObject<ThisClass>(cm));
            }));
    }
#endif
}

AAIController* UBotCheatManagerExtension::AddBot()
{
#if WITH_SERVER_CODE && UE_WITH_CHEAT_MANAGER
    if (auto botComponent = GetBotComponent())
    {
        return botComponent->Cheat_AddBot();
    }
#endif
    return nullptr;
}

void UBotCheatManagerExtension::RemoveBot()
{
#if WITH_SERVER_CODE && UE_WITH_CHEAT_MANAGER
    if (auto botComponent = GetBotComponent())
    {
        botComponent->Cheat_RemoveBot();
    }
#endif
}

void UBotCheatManagerExtension::RemoveSpecificBot(AAIController* bot)
{
#if WITH_SERVER_CODE && UE_WITH_CHEAT_MANAGER
    if (auto botComponent = GetBotComponent())
    {
        botComponent->Cheat_RemoveBot(bot);
    }
#endif
}

UBotCreationComponent* UBotCheatManagerExtension::GetBotComponent() const
{
    if (UWorld* world = GetWorld())
    {
        if (auto gm = world->GetAuthGameMode())
        {
            return gm->FindComponentByClass<UBotCreationComponent>();
        }
    }

    return nullptr;
}
