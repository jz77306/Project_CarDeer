// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyPawn.h"
#include "PlayerChess.h"
#include "EnemySoldier.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_CARDEER_API AEnemySoldier : public AEnemyPawn
{
	GENERATED_BODY()

public:
	
public:

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;
};
