// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class OMPCOURSE_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	TArray<FVector> TargetLocation;

	UPROPERTY(EditAnywhere)
	float LapTime;

	void AddActiveTrigger();
	void RemoveActiveTrigger();

private:
	TArray<FVector> GlobalTargets;
	int targetIndex;
	float speed;
	bool waitSync;
	bool reverse;
	float ellapsedTime;
	int activeTriggers = 1;
};
