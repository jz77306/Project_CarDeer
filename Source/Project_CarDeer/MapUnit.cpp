// Fill out your copyright notice in the Description page of Project Settings.


#include "MapUnit.h"

// Sets default values
AMapUnit::AMapUnit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMapUnit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMapUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

