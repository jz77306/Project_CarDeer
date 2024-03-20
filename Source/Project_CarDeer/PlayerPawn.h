// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParentCard.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class PROJECT_CARDEER_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	/** Top down camera */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
	UPROPERTY(BlueprintReadWrite)
	int NumOfCardsInHAnd = 0;

	UPROPERTY(BlueprintReadWrite)
	TArray<FVector> ArrInHandPosition;

	UPROPERTY(BlueprintReadWrite)
	bool bNoSpaceInHand = false;

	UPROPERTY(BlueprintReadWrite)
	int Mana;

public:
	UFUNCTION(BlueprintCallable)
	void ReorgnizeCards(int NumOfCard);

	UFUNCTION(BlueprintCallable)
	bool AddCard(AParentCard* NewCard);

};
