// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ParentCard.generated.h"

UCLASS()
class PROJECT_CARDEER_API AParentCard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParentCard();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//
public:

	UPROPERTY(BlueprintReadWrite)
	FVector PositionInHand;

	bool IsInHand;

	bool IsDrawed = true;
	bool bSHouldReturn;
	bool bShouldPlay;

	FVector LookAtVector;
	
	FRotator TargetRotation;
	
public:
	UFUNCTION(BlueprintCallable)
	void BindController();

	UFUNCTION(BlueprintCallable)
	void SetRotationToPlayer();

	UFUNCTION(BlueprintCallable)
	void Play();

	UFUNCTION(BlueprintCallable)
	void Return();

};
