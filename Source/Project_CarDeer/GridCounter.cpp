// Fill out your copyright notice in the Description page of Project Settings.


#include "GridCounter.h"

// Sets default values
AGridCounter::AGridCounter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void AGridCounter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGridCounter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGridCounter::UpdateRowNum()
{
	
}

void AGridCounter::UpdateColumnNum()
{
	
}

