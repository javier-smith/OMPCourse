// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
    PrimaryActorTick.bCanEverTick = true;

    SetMobility(EComponentMobility::Movable);
    UE_LOG(LogTemp, Warning, TEXT("LeWhat?"));
}

void AMovingPlatform::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        SetReplicates(true);
        SetReplicateMovement(true);
        FVector StartPosition = GetActorLocation();

        GlobalTargets.Add(StartPosition);
        float trackLength = 0;

        for (int i = 0; i < TargetLocation.Num(); i++)
        {
            FVector newPos = GetTransform().TransformPosition(TargetLocation[i]);
            GlobalTargets.Add(newPos);
            trackLength += (GlobalTargets[i + 1] - GlobalTargets[i]).Size();
        }

        speed = trackLength / LapTime;

        UE_LOG(LogTemp, Warning, TEXT("Speed: %f"), speed);
    }
}

void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (HasAuthority() && activeTriggers > 0)
    {
        ellapsedTime += DeltaTime;
        FVector Location = GetActorLocation();
        FVector currentTarget = GlobalTargets[targetIndex];
        float dist = FVector::Distance(Location, currentTarget);

        if (dist < speed * DeltaTime)
        {
            Location = currentTarget;



            if (targetIndex == 0 || targetIndex == GlobalTargets.Num() - 1)
            {
                if (ellapsedTime >= LapTime + WaitTime)
                {
                    ellapsedTime = 0;
                    reverse = !reverse;
                    UE_LOG(LogTemp, Warning, TEXT("reversing"));
                    targetIndex += reverse ? -1 : 1;
                }
            }
            else
            {
                targetIndex += reverse ? -1 : 1;
            }


        }
        else
        {
            FVector direction = (currentTarget - Location).GetSafeNormal();
            Location += direction * speed * DeltaTime;
        }

        SetActorLocation(Location);

    }

}

void AMovingPlatform::AddActiveTrigger()
{
    activeTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
    if (activeTriggers > 0)
    {
        activeTriggers--;
    }
}