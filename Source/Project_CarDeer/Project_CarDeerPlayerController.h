// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CarDeerHUD.h"
#include "CardPile.h"
#include "MapUnit.h"
#include "ParentCard.h"
#include "PlayerPawn.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "Project_CarDeerPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;

UCLASS()
class AProject_CarDeerPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AProject_CarDeerPlayerController();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
	void OnTouchPressed(const ETouchIndex::Type FingerIndex, const FVector Location);
	void OnTouchReleased(const ETouchIndex::Type FingerIndex, const FVector Location);

private:
	bool bInputPressed; // Input is bring pressed
	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed


	//Customed Logic---------------------------------------
public:
	UPROPERTY(BlueprintReadWrite)
	ACarDeerHUD* BindHUD;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<AParentCard*> CardInHandArray;

	UPROPERTY(BlueprintReadWrite)
	AParentCard* TargetCard;

	UPROPERTY(BlueprintReadWrite)
	ACardPile* TargetCardPile = nullptr;

	UPROPERTY(BlueprintReadWrite)
	AMapUnit* TargetMapUnit;

	UPROPERTY(BlueprintReadWrite)
	bool bHitCardPile;
	
	UPROPERTY(BlueprintReadWrite)
	bool bCardPlayed;

	bool IsLeftMouseDown;

	UPROPERTY(BlueprintReadWrite)
	bool bHitMapUnit = false;

	bool HaveCardInHand = false;
	
	UPROPERTY(BlueprintReadWrite)
	bool IsPlayerRound = false;

	UPROPERTY(BlueprintReadWrite)
	bool CanPlayCard = false;
	
	FVector3d LastLocation;
    	
	FRotator LastRotation;
	
	UPROPERTY(BlueprintReadWrite)
	bool HaveDrawCard = false;

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void LeftMousePress();

	UFUNCTION(BlueprintCallable)
	void LeftMouseRelease();

	UFUNCTION(BlueprintCallable)
	void LeftMouseHold();

	UFUNCTION(BlueprintCallable)
	void MoveCard(FVector WorldLocation, FVector WorldDirection);

};


