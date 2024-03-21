// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapUnit.h"
#include "GameFramework/Actor.h"
#include "GridCounter.generated.h"

UCLASS()
class PROJECT_CARDEER_API AGridCounter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridCounter();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 SumNum;

public:
	// 更新行总和
	UFUNCTION(BlueprintCallable)
	void UpdateRowNum();

	// 更新列总和
	UFUNCTION(BlueprintCallable)
	void UpdateColumnNum();
};
