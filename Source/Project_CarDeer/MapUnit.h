// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapUnit.generated.h"

UCLASS()
class PROJECT_CARDEER_API AMapUnit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapUnit();

	// 设置格子的行列索引
	void SetIndices(int32 NewRowIndex, int32 NewColumnIndex);

	// 获取格子的行索引
	int32 GetRowIndex() const { return RowIndex; }

	// 获取格子的列索引
	int32 GetColumnIndex() const { return ColumnIndex; }

protected:
	// 该格子的行列索引
	UPROPERTY(BlueprintReadOnly)
	int32 RowIndex;
	UPROPERTY(BlueprintReadOnly)
	int32 ColumnIndex;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(BlueprintReadWrite)
	bool bPlayerSteppingOn;

	UPROPERTY(BlueprintReadWrite)
	bool bEnemySteppingOn;

	UPROPERTY(BlueprintReadWrite)
	AActor* ActorSteppedOn;
	
};
