#include "BeamWalkingComponent.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

UBeamWalkingComponent::UBeamWalkingComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    bIsBeamWalking = false;
}

void UBeamWalkingComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UBeamWalkingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (bIsBeamWalking)
    {
        ConstrainMovementToBeam();
    }
}

bool UBeamWalkingComponent::DetectBeamSurface(FVector& OutBeamLocation, FVector& OutBeamNormal)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return false;

    // Starting point of the trace (character's current position)
    FVector Start = Character->GetActorLocation();
    FVector DownwardVector = FVector(0.0f, 0.0f, -1.0f);
    FVector End = Start + DownwardVector * 100.0f; // End point of the trace 100 units below the character

    // Set up a hit result for the trace
    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(Character);

    // Perform the trace
    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams);

    // Set duration for the debug line
    float TraceDuration = 2.0f;  // Trace duration in seconds

    // Draw the debug line so you can see the trace
    DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, TraceDuration, 0, 2.0f);

    // Draw a debug sphere where the trace hits to mark the impact point
    if (bHit)
    {
        FVector HitLocation = HitResult.ImpactPoint;
        FVector HitNormal = HitResult.ImpactNormal;

        // Draw the impact point as a sphere for better visibility
        DrawDebugSphere(GetWorld(), HitLocation, 10.0f, 12, FColor::Red, false, TraceDuration);

        // Check if the surface is reasonably flat (e.g., a beam surface)
        if (FMath::Abs(HitNormal.Z) > 0.8f)
        {
            OutBeamLocation = HitLocation;
            OutBeamNormal = HitNormal;
            return true;
        }
    }

    return false;
}

void UBeamWalkingComponent::ConstrainMovementToBeam()
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    FVector CurrentLocation = Character->GetActorLocation();
    FVector RightVector = Character->GetActorRightVector();
    FVector ForwardVector = Character->GetActorForwardVector();

    // Project current location onto the beam's direction (forward or backward)
    FVector ConstrainedLocation = BeamLocation + FVector::DotProduct(CurrentLocation - BeamLocation, ForwardVector) * ForwardVector;

    // Move character gradually toward the constrained position
    FVector NewLocation = FMath::VInterpTo(CurrentLocation, ConstrainedLocation, GetWorld()->GetDeltaSeconds(), 5.0f);
    Character->SetActorLocation(NewLocation);

    // Optionally, you can add some rotation logic here for balancing effect
}

void UBeamWalkingComponent::StartBeamWalking()
{
    if (!bIsBeamWalking && DetectBeamSurface(BeamLocation, BeamNormal))
    {
        bIsBeamWalking = true;
    }
}

void UBeamWalkingComponent::StopBeamWalking()
{
    bIsBeamWalking = false;
}
