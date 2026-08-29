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
    virtual void SpawnOneBot();

    /** Deletes the last created bot if possible.. */
    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
    virtual void RemoveOneBot();

#if WITH_SERVER_CODE
    void Cheat_AddBot() { SpawnOneBot(); }
    void Cheat_RemoveBot() { RemoveOneBot(); }
#endif

protected:
    UPROPERTY(EditAnywhere)
    TSubclassOf<AAIController> BotControllerClass;

    UPROPERTY(Transient)
    TArray<TObjectPtr<AAIController>> SpawnedBotList;
};
