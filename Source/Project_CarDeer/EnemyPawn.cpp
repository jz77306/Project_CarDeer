// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"

// Sets default values
AEnemyPawn::AEnemyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	StepOnTrace();

}

// Called to bind functionality to input
void AEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

AMapUnit* AEnemyPawn::StepOnTrace()
{
	FVector StartVec = this->GetActorLocation();
	FVector EndVec = this->GetActorLocation()+FVector(0,0,-200);
	FHitResult HitResult;
	bool bHaveHitRes = GetWorld()->LineTraceSingleByChannel(HitResult, StartVec, EndVec, ECC_Visibility);
	if(bHaveHitRes)
	{
		SteppedOnUnit = Cast<AMapUnit>(HitResult.GetActor());
		SteppedOnUnit->bEnemySteppingOn = true;
		SteppedOnUnit->ActorSteppedOn = this;
	}
	return SteppedOnUnit;
}

void AEnemyPawn::TakeDamageFromPlayer(int DamageAmount)
{
	Blood -= DamageAmount;
	if(Blood <= 0)
	{
		bIsDead = true;
	}
}

void AEnemyPawn::Death()
{
	
}

FVector AEnemyPawn::FindNextLocation(FVector StartLocation)
{
	FVector DestinationLoc = TargetPlayerChess->GetActorLocation();
	FVector NextLocation = this->GetActorLocation();
	if(StartLocation.X>DestinationLoc.X)
	{
		
	}
	return NextLocation;
}


