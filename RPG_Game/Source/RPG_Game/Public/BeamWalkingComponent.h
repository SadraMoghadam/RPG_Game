// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BeamWalkingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_GAME_API UBeamWalkingComponent : public UActorComponent
{
	GENERATED_BODY()

public:    
    UBeamWalkingComponent();

protected:
    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable)
    void StartBeamWalking();

    UFUNCTION(BlueprintCallable)
    void StopBeamWalking();

protected:
    bool DetectBeamSurface(FVector& OutBeamLocation, FVector& OutBeamNormal);
    void ConstrainMovementToBeam();

private:
    bool bIsBeamWalking;
    FVector BeamLocation;
    FVector BeamNormal;
};
