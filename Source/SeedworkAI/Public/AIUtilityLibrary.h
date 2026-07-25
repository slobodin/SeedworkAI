// Copyright (c) Mistfly Games. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "AIUtilityLibrary.generated.h"

class APawn;
class UBehaviorTree;

UCLASS()
class SEEDWORKAI_API UAIUtilityLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    static void SetAIValue_Bool(APawn* pawn, FName key, bool value);

    UFUNCTION(BlueprintPure)
    static bool GetAIValue_Bool(const APawn* pawn, FName key);

    UFUNCTION(BlueprintCallable)
    static void SetAIValue_Int(APawn* pawn, FName key, int32 value);

    UFUNCTION(BlueprintCallable)
    static void SetAIValue_Enum(APawn* pawn, FName key, uint8 value);

    UFUNCTION(BlueprintPure)
    static int32 GetAIValue_Int(const APawn* pawn, FName key);

    UFUNCTION(BlueprintCallable)
    static void SetAIValue_Float(APawn* pawn, FName key, float value);

    UFUNCTION(BlueprintPure)
    static float GetAIValue_Float(const APawn* pawn, FName key);

    UFUNCTION(BlueprintCallable)
    static void SetAIValue_Name(APawn* pawn, FName key, FName value);

    UFUNCTION(BlueprintPure)
    static FName GetAIValue_Name(const APawn* pawn, FName key);

    UFUNCTION(BlueprintCallable)
    static void SetAIValue_Vector(APawn* pawn, FName key, FVector value);

    UFUNCTION(BlueprintPure)
    static FVector GetAIValue_Vector(const APawn* pawn, FName key);

    UFUNCTION(BlueprintCallable)
    static void SetAIValue_Actor(APawn* pawn, FName key, AActor* value);

    UFUNCTION(BlueprintPure)
    static AActor* GetAIValue_Actor(const APawn* pawn, FName key);

    UFUNCTION(BlueprintCallable)
    static void StartBehaviour(APawn* pawn, UBehaviorTree* newBehaviour);

    UFUNCTION(BlueprintCallable)
    static void StartDefaultBehaviour(APawn* pawn);
};
