// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));

	if (HasAuthority()) 
	{
		SetReplicates(true);
		SetReplicateMovement(true);
		FVector StartPosition = GetActorLocation();
		//GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);

		GlobalTargets.Add(StartPosition);

		for (int i = 1; i < TargetLocation.Num(); i++)
		{
			GlobalTargets.Add(StartPosition + TargetLocation[i]);
		}

		speed = LapTime;
	}
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("Ticking"));

	if (HasAuthority() && activeTriggers > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Has auth n shit"));
		ellapsedTime += DeltaTime;
		FVector Location = GetActorLocation();
		FVector currentTarget = GlobalTargets[targetIndex];
		float dist = FVector::Distance(Location, currentTarget);

		if (dist < speed * DeltaTime)
		{
			Location = currentTarget;

			if (ellapsedTime >= LapTime) {
				ellapsedTime = 0;

				if (targetIndex == 0 || targetIndex == GlobalTargets.Num())
				{
					reverse = !reverse;
					UE_LOG(LogTemp, Warning, TEXT("reversing"));
				} 

				targetIndex += reverse ? -1 : 1;
			}
		} 
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Adding speed"));
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