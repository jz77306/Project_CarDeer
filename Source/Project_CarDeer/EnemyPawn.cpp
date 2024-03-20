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

	if(!bIsMoving) StepOnTrace();
	MoveTo(Destination);
	if(this->GetActorLocation() == Destination) bIsMoving = false;

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
		SelfIndexX = SteppedOnUnit->GetRowIndex();
		SelfIndexY = SteppedOnUnit->GetColumnIndex();
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

FVector2D AEnemyPawn::FindNextLocation(FVector StartLocation)
{
	FVector DestinationLoc = TargetPlayerChess->GetActorLocation();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White,TargetPlayerChess->GetActorLocation().ToString());
	FVector2D NextLocation = FVector2D(0, 0);
	int TargetRow = -1, TargetColumn = -1;
	TargetRow = SteppedOnUnit->GetRowIndex();
	TargetColumn = SteppedOnUnit->GetColumnIndex();
	
	float Seed = FMath::FRand();
	float XorYValve = FMath::FRand();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White,FVector2D(Seed, XorYValve).ToString());
	if(Seed<=0.8)
	{
		if(StartLocation.X>DestinationLoc.X)
		{
			if(XorYValve<0.5)
			{
				TargetRow = SteppedOnUnit->GetRowIndex()+1;
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White,FString::FromInt(TargetColumn));
			}
			else
			{
				if(StartLocation.Y > DestinationLoc.Y)
				{
					TargetColumn = SteppedOnUnit->GetColumnIndex()-1;
				}
				else
				{
					TargetColumn = SteppedOnUnit->GetColumnIndex()+1;
				}
			}

		}
		else
		{
			if(XorYValve<0.5)
			{
				TargetRow = SteppedOnUnit->GetRowIndex()-1;
			}
			else
			{
				if(StartLocation.Y > DestinationLoc.Y)
				{
					TargetColumn = SteppedOnUnit->GetColumnIndex()-1;
				}
				else
				{
					TargetColumn = SteppedOnUnit->GetColumnIndex()+1;
				}
			}

		}
	}
	else if(Seed != 0.9)
	{
		if(XorYValve<0.5) TargetRow = SteppedOnUnit->GetColumnIndex()+ (1*(Seed-0.9)/abs(Seed-0.9));
		else TargetColumn = SteppedOnUnit->GetRowIndex()+1*(Seed-0.9)/abs(Seed-0.9);
	}
	
	if(TargetRow >= 0 && TargetRow < 5 && TargetColumn >= 0 && TargetColumn < 5 && abs(SteppedOnUnit->GetRowIndex()-TargetRow)+abs(SteppedOnUnit->GetColumnIndex()-TargetColumn) == 1)
	{
		NextLocation = FVector2D(TargetRow, TargetColumn);
	}
	return NextLocation;
}

void AEnemyPawn::MoveTo(FVector MoveToLocation)
{
	this->SetActorLocation(FMath::VInterpTo(this->GetActorLocation(), MoveToLocation, 0.2,0.5));
}


