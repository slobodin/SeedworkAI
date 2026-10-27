// Copyright (c) Mistfly Games. All Rights Reserved.

#pragma once

#include "GameFramework/CheatManager.h"
#include "BotCheatManagerExtension.generated.h"

class AAIController;
class UBotCreationComponent;

/** Cheats related to bots */
UCLASS(NotBlueprintable)
class SEEDWORKAI_API UBotCheatManagerExtension final : public UCheatManagerExtension
{
    GENERATED_BODY()

public:
    UBotCheatManagerExtension();

    // Adds a bot player
    UFUNCTION(Exec, BlueprintAuthorityOnly)
    AAIController* AddBot();

    // Removes a bot player
    UFUNCTION(Exec, BlueprintAuthorityOnly)
    void RemoveBot();

    // Removes the given bot player
    void RemoveSpecificBot(AAIController* bot);

private:
    UBotCreationComponent* GetBotComponent() const;
};
