// Copyright (c) Mistfly Games. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "BotCreationComponent.generated.h"

class AAIController;

UCLASS(Abstract, Blueprintable, meta = (BlueprintSpawnableComponent))
class SEEDWORKAI_API UBotCreationComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UBotCreationComponent();

    /** Always creates a single bot. */
    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
    AAIController* SpawnOneBot();

    /** Deletes the last created bot if possible.. */
    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
    void RemoveOneBot();

    /** Deletes the given bot if this component created it. */
    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
    void RemoveBot(AAIController* bot);

#if WITH_SERVER_CODE
    AAIController* Cheat_AddBot() { return SpawnOneBot(); }
    void Cheat_RemoveBot() { RemoveOneBot(); }
    void Cheat_RemoveBot(AAIController* bot) { RemoveBot(bot); }
#endif

protected:
    UPROPERTY(EditAnywhere)
    TSubclassOf<AAIController> BotControllerClass;

    UPROPERTY(Transient)
    TArray<TObjectPtr<AAIController>> SpawnedBotList;
};
