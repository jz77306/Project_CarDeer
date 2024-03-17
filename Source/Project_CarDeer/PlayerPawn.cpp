// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "DSP/Chorus.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1100.f;
	CameraBoom->SetRelativeRotation(FRotator(-55.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	TopDownCameraComponent->SetFieldOfView(95.0);

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ReorgnizeCards(NumOfCardsInHAnd);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerPawn::ReorgnizeCards(int NumOfCard)
{
	FVector CenterPosition = FVector(350, 1800, 100);
	FVector GapUnit = FVector(0, 64, 0);
	FVector AdjustVec = FVector(0, 0, 0);
	if(NumOfCard == 0)
	{
		return;
	}
	if(NumOfCard == 1)
	{
		ArrCardInHand[0]->SetActorLocation(FMath::VInterpTo(ArrCardInHand[0]->GetActorLocation(), CenterPosition, 0.2, 0.2));
		ArrCardInHand[0]->PositionInHand = CenterPosition;
	}
	
	if(NumOfCard == 2)
	{
		ArrCardInHand[0]->PositionInHand = CenterPosition+GapUnit;
		ArrCardInHand[0]->SetActorLocation(FMath::VInterpTo(ArrCardInHand[0]->GetActorLocation(), ArrCardInHand[0]->PositionInHand, 0.2, 0.2));
		ArrCardInHand[1]->PositionInHand = CenterPosition-GapUnit;
		ArrCardInHand[1]->SetActorLocation(FMath::VInterpTo(ArrCardInHand[1]->GetActorLocation(), ArrCardInHand[1]->PositionInHand, 0.2, 0.2));
	}
	
	if(NumOfCard >= 3 && NumOfCard <= 6)
	{
		if(NumOfCard%2 == 1)
		{
			ArrCardInHand[0]->PositionInHand = CenterPosition;
			ArrCardInHand[0]->SetActorLocation(FMath::VInterpTo(ArrCardInHand[0]->GetActorLocation(), ArrCardInHand[0]->PositionInHand, 0.2, 0.2));
			ArrCardInHand[1]->PositionInHand = CenterPosition-2*GapUnit;
			ArrCardInHand[1]->SetActorLocation(FMath::VInterpTo(ArrCardInHand[1]->GetActorLocation(), ArrCardInHand[1]->PositionInHand, 0.2, 0.2));
			
			for(int iter = 2;iter<NumOfCard;iter++)
			{
					ArrCardInHand[iter]->PositionInHand = ArrCardInHand[iter-2]->PositionInHand-4*GapUnit*(iter%2-0.5)-AdjustVec;
					ArrCardInHand[iter]->SetActorLocation(FMath::VInterpTo(ArrCardInHand[iter]->GetActorLocation(), ArrCardInHand[iter]->PositionInHand, 0.2, 0.2));
			}
		}
		else
		{
			ArrCardInHand[0]->PositionInHand = CenterPosition+GapUnit;
			ArrCardInHand[0]->SetActorLocation(FMath::VInterpTo(ArrCardInHand[0]->GetActorLocation(), ArrCardInHand[0]->PositionInHand, 0.2, 0.2));
			ArrCardInHand[1]->PositionInHand = CenterPosition-GapUnit;
			ArrCardInHand[1]->SetActorLocation(FMath::VInterpTo(ArrCardInHand[1]->GetActorLocation(), ArrCardInHand[1]->PositionInHand, 0.2, 0.2));

			for(int iter = 2;iter<NumOfCard;iter++)
			{
				ArrCardInHand[iter]->PositionInHand = ArrCardInHand[iter-2]->PositionInHand-4*GapUnit*(iter%2-0.5)-AdjustVec;
				ArrCardInHand[iter]->SetActorLocation(FMath::VInterpTo(ArrCardInHand[iter]->GetActorLocation(), ArrCardInHand[iter]->PositionInHand, 0.2, 0.2));
			}
		}
	}

	else
	{
		bNoSpaceInHand = true;
	}
}

bool APlayerPawn::AddCard(AParentCard* NewCard)
{
	if(NumOfCardsInHAnd < 6)
	{
		ArrCardInHand.Add(NewCard);
		NumOfCardsInHAnd += 1;
	}
	else if(NumOfCardsInHAnd >= 6)
	{
		NewCard->bSHouldBurn= true;
	}
	return NewCard->bSHouldBurn;
}

