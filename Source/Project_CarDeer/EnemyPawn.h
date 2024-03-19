// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapUnit.h"
#include "PlayerChess.h"
#include "GameFramework/Pawn.h"
#include "EnemyPawn.generated.h"

UCLASS()
class PROJECT_CARDEER_API AEnemyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(BlueprintReadWrite, Category="Attribute")
	int Blood;

	UPROPERTY(BlueprintReadWrite)
	bool bIsDead;

	UPROPERTY(BlueprintReadWrite)
	bool bReadyToAction;

	UPROPERTY(BlueprintReadWrite)
	FVector Destination;
	
	UPROPERTY(BlueprintReadWrite)
	APlayerChess* TargetPlayerChess;

public:
	UFUNCTION(BlueprintCallable)
	AMapUnit* StepOnTrace();

	UFUNCTION(BlueprintCallable)
	void TakeDamageFromPlayer(int DamageAmount);

	UFUNCTION(BlueprintCallable)
	void Death();


};
