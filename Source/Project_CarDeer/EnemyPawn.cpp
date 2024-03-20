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
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White,FString::FromInt(SteppedOnUnit->GetRowIndex()));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White,FString::FromInt(SteppedOnUnit->GetColumnIndex()));
	FVector DestinationLoc = TargetPlayerChess->GetActorLocation();
	FVector NextLocation = this->GetActorLocation();
	int TargetRow = -1, TargetColumn = -1, count = 0;
	do
	{
		TargetRow = SteppedOnUnit->GetRowIndex();
		TargetColumn = SteppedOnUnit->GetColumnIndex();
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
			
			if(XorYValve<0.5) TargetColumn = SteppedOnUnit->GetColumnIndex()+ (1*(Seed-0.85)/abs(Seed-0.85));
			else TargetRow = SteppedOnUnit->GetRowIndex()+1*(Seed-0.85)/abs(Seed-0.85);
		}
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White,FString::FromInt(TargetRow));
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White,FString::FromInt(TargetColumn));
		
		if(TargetRow >= 0 && TargetRow < 5 && TargetColumn >= 0 && TargetColumn < 5 /*&& MapArranger->GetMapUnitInstance(TargetRow, TargetColumn)->bEnemySteppingOn == false*/)
		{
			//NextLocation = MapArranger->GetMapUnitInstance(TargetRow, TargetColumn)->GetActorLocation();
			break;
		}
		
		count++;
		if(count == 20)
		{
			NextLocation = this->GetActorLocation();
			break;
		}
	}
	while(1);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White,FString::FromInt(TargetRow));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White,FString::FromInt(TargetColumn));
	NextLocation.Z = this->GetActorLocation().Z;
	return NextLocation;
	
}

void AEnemyPawn::MoveTo(FVector MoveToLocation)
{
	this->SetActorLocation(FMath::VInterpTo(this->GetActorLocation(), MoveToLocation, 0.2,0.5));
}


