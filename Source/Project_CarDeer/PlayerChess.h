// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapUnit.h"
#include "GameFramework/Pawn.h"
#include "PlayerChess.generated.h"

UCLASS()
class PROJECT_CARDEER_API APlayerChess : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerChess();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(BlueprintReadWrite)
	int SelfIndexX;

	UPROPERTY(BlueprintReadWrite)
	int SelfIndexY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AMapUnit* SteppedOnUnit;

	UPROPERTY(BlueprintReadWrite)
	bool bIsMoving = false;

	UPROPERTY(BlueprintReadWrite)
	FVector Destination;

public:
	UFUNCTION(BlueprintCallable)
	void MoveTo(FVector MoveToLocation);
};
