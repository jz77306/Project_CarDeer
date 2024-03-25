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

	//初始化格子随机数
	UFUNCTION(BlueprintCallable)
	void InitRandUnitNum();

	//————————————————————————————Set————————————————————————————
	// 设置格子的行列索引
	void SetIndices(int32 NewRowIndex, int32 NewColumnIndex);

	// 设置格子
	void SetUnitNum(int32 NewUnitNum);

	//————————————————————————————Get————————————————————————————
	// 获取格子的行索引
	UFUNCTION(BlueprintCallable)
	int32 GetRowIndex() const { return RowIndex; }

	// 获取格子的列索引
	UFUNCTION(BlueprintCallable)
	int32 GetColumnIndex() const { return ColumnIndex; }
	
	
	// 获取格子的内部数字
	UFUNCTION(BlueprintCallable)
	int32 GetUnitNum() const { return UnitNum; }

	//————————————————————————————Update—————————————————————————
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateUnitNumShow();
	
	
protected:
	// 该格子的行列索引
	UPROPERTY(BlueprintReadOnly)
	int32 RowIndex;
	UPROPERTY(BlueprintReadOnly)
	int32 ColumnIndex;

	// 该格子内部数字
	UPROPERTY(BlueprintReadOnly)
	int32 UnitNum;
	
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

	//该格子是否可操作
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bCanbeOprate;

	UPROPERTY(BlueprintReadWrite)
	int32 Digit = 0;

	UPROPERTY(BlueprintReadWrite)
	AActor* ActorSteppedOn;
	
};
