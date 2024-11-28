// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameUtilities.generated.h"

/**
 * 
 */
UCLASS()
class RPG_GAME_API UGameUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Math")
	static int32 GetSign(int32 Value);
};
