// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapUnit.h"
//#include "MapArranger.h"
#include "GameFramework/Actor.h"
#include "GridCounter.generated.h"

UENUM()
enum class ERowColumnMark : uint8
{
	EC_Row,
	EC_Column,
	EC_Defult
};

class AMapArranger;
UCLASS()
class PROJECT_CARDEER_API AGridCounter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridCounter();

	//————————————————————————————Set————————————————————————————————————
	// 设置行列标注
	UFUNCTION(BlueprintCallable)
	void SetRowColMark(ERowColumnMark NewMark);

	//设置棋盘管理实例引用
	UFUNCTION(BlueprintCallable)
	void SetMapArranger(AMapArranger* MapArrangerInst);

	UFUNCTION(BlueprintCallable)
	void SetRowColIndex(int32 NewIndex);

	//————————————————————————————Get————————————————————————————————————
	UFUNCTION(BlueprintCallable)
	int32 GetSumNum() const {return SumNum;}

	UFUNCTION(BlueprintCallable)
	int32 GetRowColIndex() const {return RowColIndex;}
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	//计数器总和
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 SumNum;

	//计数器行列索引: 标记为Row则为RowIndex 标记为Column则为ColumnIndex
	int32 RowColIndex;

	//行列标记
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ERowColumnMark RowColMark;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	AMapArranger* MapArranger;
	
public:
	
	// 更新总和
	UFUNCTION(BlueprintCallable)
	void UpdateCountersNum();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateCountersNumShow();
	

};
