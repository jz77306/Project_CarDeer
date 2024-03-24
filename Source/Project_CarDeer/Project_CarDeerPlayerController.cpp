// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_CarDeerPlayerController.h"

#include "EnemyPawn.h"
#include "MapUnit.h"
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


TArray<int32> AProject_CarDeerPlayerController::GenerateRangeArray() const
{
	TArray<int32> RangeArray;

	int32 TotalWeight = 0;
	for (const FCardTypeInfo& CardType : CardTypes)
	{
		TotalWeight += CardType.Weight;
		RangeArray.Add(TotalWeight);
	}

	return RangeArray;
}

TSubclassOf<AActor> AProject_CarDeerPlayerController::RandomCardType(const TArray<int32>& RangeArray) const
{
	// 生成0到总权值-1的随机数
	int32 RandomNumber = FMath::RandRange(0, RangeArray.Last() - 1);

	// 区间数组中找随机数de 所在区间
	for (int32 Index = 0; Index < RangeArray.Num(); ++Index)
	{
		if (RandomNumber < RangeArray[Index])
		{
			return CardTypes[Index].CardType;
		}
	}
	
	return nullptr;
}

void AProject_CarDeerPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//Bind Customed HUD
	BindHUD = Cast<ACarDeerHUD>(GetHUD());
}

//左键点击事件
void AProject_CarDeerPlayerController::LeftMousePress()
{
	IsLeftMouseDown = true;
	FHitResult HitResult;
	AParentCard* ParentCard = New<AParentCard>(FMemStack::Get(), 1);
	ACardPile* CardPile = New<ACardPile>(FMemStack::Get(), 1);
	GetHitResultUnderCursor(ECC_Visibility, true, HitResult);
	//点击选中卡牌
	if(Cast<AParentCard>(HitResult.GetActor())  && Cast<AParentCard>(HitResult.GetActor())->bCanSelect)
	{
		TargetCard = Cast<AParentCard>(HitResult.GetActor());
		TargetCard->bShouldPlay = false;
		TargetCard->bSHouldReturn = false;
		HaveCardInHand = true;
		TargetCard->bIsSelected = true;
		//TargetCard->bIsReleaseed = false;
		TargetCard->SetActorRotation(FRotator(270,0,0));
		LastLocation = TargetCard->GetActorLocation();
		LastRotation = TargetCard->GetActorRotation();

	}
	//点击触发牌堆抽卡
	else if(Cast<ACardPile>(HitResult.GetActor()))
	{
		if(!TargetCardPile)
		{
			TargetCardPile = Cast<ACardPile>(HitResult.GetActor());
		}
		if(!HaveDrawCard)
		{
			bHitCardPile = true;
		}
	}
	//点击对目标地格释放效果
	else if(Cast<AMapUnit>(HitResult.GetActor()))
	{
		bHitMapUnit = true;
		TargetMapUnit = Cast<AMapUnit>(HitResult.GetActor());
	}
	else if(Cast<AEnemyPawn>(HitResult.GetActor()))
	{
		bHitMapUnit = true;
		TargetMapUnit = Cast<AEnemyPawn>(HitResult.GetActor())->SteppedOnUnit;
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue,TEXT("Left Mouse Down"));
}

//左键释放事件
void AProject_CarDeerPlayerController::LeftMouseRelease()
{
	if(TargetCard)
	{
		if(TargetCard->bIsInDeployZone)
		{
			TargetCard->bShouldPlay = true;
			HaveCardInHand = false;
			bCardPlayed = true;
		}
		else
		{
			TargetCard->bSHouldReturn = true;
			HaveCardInHand = false;
			bCardPlayed = false;
		}
		TargetCard->bIsSelected = false;
		TargetCard = nullptr;
	}
	if(bHitMapUnit)
	{
		bHitMapUnit = false;
	}
	
	IsLeftMouseDown = false;
}

void AProject_CarDeerPlayerController::LeftMouseHold()
{
	if(HaveCardInHand)
	{
		FVector WorldLocation;
		FVector WorldDirection;
		DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
		MoveCard(WorldLocation, WorldDirection);
	}
}

void AProject_CarDeerPlayerController::MoveCard(FVector WorldLocation, FVector WorldDirection)
{
	TargetCard->SetActorLocation(FMath::VInterpTo(TargetCard->GetActorLocation(), WorldLocation+WorldDirection*1250, 0.2, 1.2));

	FVector3d MoveLocation = LastLocation - TargetCard->GetActorLocation();
	LastLocation = TargetCard->GetActorLocation();
	LastRotation = TargetCard->GetActorRotation();
	LastRotation.Pitch = 270;
	FRotator TargetRotator;
	FRotator NowRotator;
	TargetRotator.Pitch = 270;
	TargetRotator.Yaw = 0;
	TargetRotator.Roll = 180;
	NowRotator = TargetRotator;
	NowRotator.Roll = TargetRotator.Roll + MoveLocation.Y*0.3;
	NowRotator.Pitch = TargetRotator.Pitch + MoveLocation.X*0.8;
	TargetCard->SetActorRotation(NowRotator);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *TargetCard->GetActorRotation().ToString());
	float YVecComp = TargetCard->GetActorLocation().Y;
	
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White,TargetCard->GetActorLocation().ToString());
	if(YVecComp >CardingArea)
	{
		if(IsPlayerRound && CanPlayCard)
		{
			// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White,TEXT("true"));
			TargetCard->bIsInDeployZone = true;
		}
	}
	else
	{
		// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White,TEXT("false"));
		TargetCard->bIsInDeployZone = false;
	}
}

TSubclassOf<AActor> AProject_CarDeerPlayerController::GetRandomCardType() const
{
	TArray<int32> RangeArray = GenerateRangeArray();
	TSubclassOf<AActor> SelectedCardType = RandomCardType(RangeArray);
	return SelectedCardType;
}

