// Fill out your copyright notice in the Description page of Project Settings.


#include "CardPile.h"

#include "Tasks/GameplayTask_SpawnActor.h"

// Sets default values
ACardPile::ACardPile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACardPile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACardPile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AParentCard* ACardPile::Draw()
{
	/*
	int CardIndex = FMath::RandRange(0, CardsInStack.Num()-1);
	AParentCard* SelectedCard = CardsInStack[CardIndex];
	CardsInStack.Remove(SelectedCard);
	return SelectedCard;
	*/
	UWorld::SpawnActor<AParentCard>();
	
}

