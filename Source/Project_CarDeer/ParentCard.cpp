// Fill out your copyright notice in the Description page of Project Settings.


#include "ParentCard.h"

#include "Project_CarDeerCharacter.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
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
}

// Called every frame
void AParentCard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(IsDrawed)
	{
		SetRotationToPlayer();
	}
	
}

void AParentCard::BindController()
{
	
}

void AParentCard::SetRotationToPlayer()
{
	AProject_CarDeerCharacter* PlayerPawn = Cast<AProject_CarDeerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	FVector PlayerLocation = PlayerPawn->GetTopDownCameraComponent()->GetComponentLocation();
	LookAtVector = this->GetActorLocation()-PlayerLocation;
	this->TargetRotation = LookAtVector.Rotation();
}


