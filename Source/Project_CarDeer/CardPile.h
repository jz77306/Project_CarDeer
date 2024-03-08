// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParentCard.h"
#include "GameFramework/Actor.h"
#include "CardPile.generated.h"

UCLASS()
class PROJECT_CARDEER_API ACardPile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACardPile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
//Customed Properties&Functions
public:
	UPROPERTY(BlueprintReadWrite)
	TArray<AParentCard*> CardsInStack;

	UPROPERTY(BlueprintReadWrite)
	int MaxCardNum;
};
