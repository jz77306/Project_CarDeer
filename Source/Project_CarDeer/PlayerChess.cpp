// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChess.h"

#include "MapUnit.h"

// Sets default values
APlayerChess::APlayerChess()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerChess::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerChess::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if(!bIsMoving)SteppedOnTrace();
}

// Called to bind functionality to input
void APlayerChess::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerChess::SteppedOnTrace()
{
	FVector StartVec = this->GetActorLocation();
	FVector EndVec = this->GetActorLocation()+FVector(0,0,-200);
	FHitResult HitResult;
	bool bHaveHitRes = GetWorld()->LineTraceSingleByChannel(HitResult, StartVec, EndVec, ECC_Visibility);
	if(bHaveHitRes)
	{
		SteppedOnUnit = Cast<AMapUnit>(HitResult.GetActor());
		SteppedOnUnit->bPlayerSteppingOn = true;
		SteppedOnUnit->ActorSteppedOn = this;
		SelfIndexX = SteppedOnUnit->GetRowIndex();
		SelfIndexY = SteppedOnUnit->GetColumnIndex();
	}
}

