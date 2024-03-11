// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_CarDeerPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "PlayerPawn.h"
#include "Project_CarDeerCharacter.h"
#include "Engine/World.h"

AProject_CarDeerPlayerController::AProject_CarDeerPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

}

//Default Cintroller Functions
void AProject_CarDeerPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if(bInputPressed)
	{
		FollowTime += DeltaTime;

		// Look for the touch location
		FVector HitLocation = FVector::ZeroVector;
		FHitResult Hit;
		if(bIsTouch)
		{
			GetHitResultUnderFinger(ETouchIndex::Touch1, ECC_Visibility, true, Hit);
		}
		else
		{
			GetHitResultUnderCursor(ECC_Visibility, true, Hit);
		}
		HitLocation = Hit.Location;

		// Direct the Pawn towards that location
		APawn* const MyPawn = GetPawn();
		if(MyPawn)
		{
			FVector WorldDirection = (HitLocation - MyPawn->GetActorLocation()).GetSafeNormal();
			MyPawn->AddMovementInput(WorldDirection, 1.f, false);
		}
	}
	else
	{
		FollowTime = 0.f;
	}

	if(IsLeftMouseDown)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White,TEXT("LMouseHold"));
		LeftMouseHold();
	}
	
}

void AProject_CarDeerPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AProject_CarDeerPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AProject_CarDeerPlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AProject_CarDeerPlayerController::OnTouchPressed);
	InputComponent->BindTouch(EInputEvent::IE_Released, this, &AProject_CarDeerPlayerController::OnTouchReleased);

}

void AProject_CarDeerPlayerController::OnSetDestinationPressed()
{
	// We flag that the input is being pressed
	bInputPressed = true;
	// Just in case the character was moving because of a previous short press we stop it
	StopMovement();
}

void AProject_CarDeerPlayerController::OnSetDestinationReleased()
{
	// Player is no longer pressing the input
	bInputPressed = false;

	// If it was a short press
	if(FollowTime <= ShortPressThreshold)
	{
		// We look for the location in the world where the player has pressed the input
		FVector HitLocation = FVector::ZeroVector;
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, true, Hit);
		HitLocation = Hit.Location;

		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, HitLocation);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, HitLocation, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}
}

void AProject_CarDeerPlayerController::OnTouchPressed(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	bIsTouch = true;
	OnSetDestinationPressed();
}

void AProject_CarDeerPlayerController::OnTouchReleased(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

//Customed Function-Declerations Below----------------------------------------------------------------------------------

void AProject_CarDeerPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//Bind Customed HUD
	BindHUD = Cast<ACarDeerHUD>(GetHUD());
	BindPlayer = Cast<APlayerPawn>(GetLocalPlayer());
}

void AProject_CarDeerPlayerController::LeftMousePress()
{
	IsLeftMouseDown = true;
	FHitResult HitResult;
	AParentCard* ParentCard = New<AParentCard>(FMemStack::Get(), 1);
	ACardPile* CardPile = New<ACardPile>(FMemStack::Get(), 1);
	GetHitResultUnderCursor(ECC_Visibility, true, HitResult);
	if(Cast<AParentCard>(HitResult.GetActor()))
	{
		TargetCard = Cast<AParentCard>(HitResult.GetActor());
		TargetCard->bShouldPlay = false;
		TargetCard->bSHouldReturn = false;
		HaveCardInHand = true;
	}
	else if(Cast<ACardPile>(HitResult.GetActor()))
	{
		if(!TargetCardPile)
		{
			TargetCardPile = Cast<ACardPile>(HitResult.GetActor());
		}
		if(!HaveDrawCard)
		{
			DrawCard();
			HaveDrawCard = true;
		}
	
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue,TEXT("Left Mouse Down"));
}

void AProject_CarDeerPlayerController::LeftMouseRelease()
{
	if(TargetCard)
	{
		if(TargetCard->bIsInDeployZone)
		{
			TargetCard->bShouldPlay = true;
			HaveCardInHand = false;
			BindPlayer->ArrCardInHand.Remove(TargetCard);
			BindPlayer->NumOfCardsInHAnd -= 1;
			BindPlayer->ReorgnizeCards(BindPlayer->NumOfCardsInHAnd);
		}
		else
		{
			TargetCard->bSHouldReturn = true;
			HaveCardInHand = false;
		}
		TargetCard = nullptr;
	}
	IsLeftMouseDown = false;
}

void AProject_CarDeerPlayerController::LeftMouseHold()
{
	if(HaveCardInHand)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White,TEXT("ShouldMoveCard"));
		FVector WorldLocation;
		FVector WorldDirection;
		DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White,WorldLocation.ToString());
		MoveCard(WorldLocation, WorldDirection);
		//TargetCard->SetActorLocation(FMath::VInterpTo(TargetCard->GetActorLocation(), WorldLocation+WorldDirection*1200, 0.2, 2));
	}
}

void AProject_CarDeerPlayerController::MoveCard(FVector WorldLocation, FVector WorldDirection)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White,WorldLocation.ToString());
	TargetCard->SetActorLocation(FMath::VInterpTo(TargetCard->GetActorLocation(), WorldLocation+WorldDirection*1250, 0.2, 2));
	float ZVecComp = TargetCard->GetActorLocation().Z;
	if(ZVecComp >400.0f)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White,TEXT("true"));
		TargetCard->bIsInDeployZone = true;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White,TEXT("false"));
		TargetCard->bIsInDeployZone = false;
	}
}

void AProject_CarDeerPlayerController::DrawCard()
{	
	AParentCard* NewCard = TargetCardPile->Draw();
	BindPlayer->ArrCardInHand.Add(NewCard);
	BindPlayer->NumOfCardsInHAnd+=1;
	BindPlayer->ReorgnizeCards(BindPlayer->NumOfCardsInHAnd);
	
}


