// Copyright (c) Mistfly Games. All Rights Reserved.

#pragma once

#include "GameFramework/CheatManager.h"
#include "BotCheatManagerExtension.generated.h"

class UBotCreationComponent;

/** Cheats related to bots */
UCLASS(NotBlueprintable)
class UBotCheatManagerExtension final : public UCheatManagerExtension
{
    GENERATED_BODY()

public:
    UBotCheatManagerExtension();

    // Adds a bot player
    UFUNCTION(Exec, BlueprintAuthorityOnly)
    void AddBot();

    // Removes a bot player
    UFUNCTION(Exec, BlueprintAuthorityOnly)
    void RemoveBot();

private:
    UBotCreationComponent* GetBotComponent() const;
};
