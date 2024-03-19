// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"

#include "Net/Core/Connection/NetConnectionFaultRecoveryBase.h"

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
	Destination = this->GetActorLocation();
}

// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	StepOnTrace();
	MoveTo(Destination);

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
	int TargetRow, TargetColumn;
	float Seed = FMath::FRand();
	float XorYValve = FMath::FRand();
	if(Seed<=0.7)
	{
		if(StartLocation.X>DestinationLoc.X)
		{
			if(XorYValve<0.5)
			{
				TargetColumn = SteppedOnUnit->GetColumnIndex()-1;
			}
			else
			{
				if(StartLocation.Y > DestinationLoc.Y)
				{
					TargetRow = SteppedOnUnit->GetRowIndex()-1;
				}
				else
				{
					TargetRow = SteppedOnUnit->GetRowIndex()+1;
				}
			}

		}
		else
		{
			if(XorYValve<0.5)
			{
				TargetColumn = SteppedOnUnit->GetColumnIndex()+1;
			}
			else
			{
				if(StartLocation.Y > DestinationLoc.Y)
				{
					TargetRow = SteppedOnUnit->GetRowIndex()-1;
				}
				else
				{
					TargetRow = SteppedOnUnit->GetRowIndex()+1;
				}
			}

		}
	}
	else
	{
		TargetColumn = SteppedOnUnit->GetColumnIndex()+ (1*(Seed-0.85)/abs(Seed-0.85));
		TargetRow = SteppedOnUnit->GetRowIndex()+1*(Seed-0.85)/abs(Seed-0.85);
	}
	NextLocation = MapArranger->GetMapUnitInstance(TargetRow, TargetColumn)->GetActorLocation();
	NextLocation.Z = this->GetActorLocation().Z;
	return NextLocation;
	
}

void AEnemyPawn::MoveTo(FVector MoveToLocation)
{
	this->SetActorLocation(FMath::VInterpTo(this->GetActorLocation(), MoveToLocation, 0.2,0.5));
}


