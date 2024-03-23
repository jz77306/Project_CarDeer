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
	for(int iter = 0; iter<=6; iter++) ArrInHandPosition.Add(FVector(0, 0, 0));
	
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

	//FVector AdjustVec = FVector(0, 0, 0);
	if(NumOfCard == 0)
	{
		return;
	}
	if(NumOfCard > 0 && NumOfCard <= 6)
	{
		ArrInHandPosition[0] = CenterPosition;
		for(int iter = 1; iter <= NumOfCard; iter++)
		{
			ArrInHandPosition[iter] = ArrInHandPosition[iter-1] += GapUnit;
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
		NumOfCardsInHAnd += 1;
	}
	else if(NumOfCardsInHAnd >= 6)
	{
		NewCard->bSHouldBurn= true;
	}
	return NewCard->bSHouldBurn;
}

