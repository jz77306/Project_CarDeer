// Fill out your copyright notice in the Description page of Project Settings.


#include "ParentCard.h"

#include "NiagaraComponentPool.h"
#include "PlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AParentCard::AParentCard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AParentCard::BeginPlay()
{
	Super::BeginPlay();
	IsDrawed = true;
	
	//测试用，设置手牌位置，后面重构
	//PositionInHand = this->GetActorLocation();
	PositionInHand = FVector(450, 1600, 100);
}

// Called every frame
void AParentCard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsDrawed)
	{
		SetRotationToPlayer();
	}
	if(bSHouldBurn)
	{
		BurnSelf();
	}
	else
	{
		if(bShouldPlay)
		{
			Play();
		}
		else if(bSHouldReturn)
		{
			Return();
		}
	}
}

void AParentCard::BindController()
{
	
}

void AParentCard::SetRotationToPlayer()
{
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetName());
	APlayerPawn* PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	FVector PlayerLocation = PlayerPawn->TopDownCameraComponent->GetComponentLocation();
	PlayerLocation.X = this->GetActorLocation().X-50;
	LookAtVector = this->GetActorLocation()-PlayerLocation;
	LookAtVector.Y = 0;
	TargetRotation = LookAtVector.Rotation();
	this->SetActorRotation(FMath::RInterpTo(this->GetActorRotation(), TargetRotation, 0.2,0.5));
}

void AParentCard::Play()
{
	
}

void AParentCard::Return()
{
	if(bIsReleaseed)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White,TEXT("true"));
		this->SetActorRotation(FMath::RInterpTo(this->GetActorRotation(), FRotator(270,0,0), 0.2, 2));
		this->SetActorLocation(FMath::VInterpTo(this->GetActorLocation(), PositionInHand, 0.2, 2));
	}
}

void AParentCard::BurnSelf()
{
	this->SetActorLocation(FMath::VInterpTo(this->GetActorLocation(), FVector(800, 1600, 200), 0.2, 0.8));
}


