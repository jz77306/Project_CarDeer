// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapUnit.h"
#include "GameFramework/Actor.h"
#include "MapArranger.generated.h"

UCLASS()
class PROJECT_CARDEER_API AMapArranger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties

	AMapArranger();

	// 创建棋盘函数
	UFUNCTION(BlueprintCallable)
	void CreateChessboard(int32 Size);

	// 摆放棋子函数
	//void PlaceChessPiece(AChessPiece* ChessPiece, int32 Row, int32 Column);

	//——————————————————————————————查询——————————————————————————————————
	// 查询格子的位置，返回FVector
	UFUNCTION(BlueprintCallable)
	FVector GetMapUnitLoc(int32 row, int32 col);

	// 查询格子的实例：输入row、col ； 返回AMapUnit*
	UFUNCTION(BlueprintCallable)
	AMapUnit* GetMapUnitInstance(int32 row, int32 col);

	// 查询格子的单行实例：输入row、col ； 返回TArray<AMapUnit*>
	UFUNCTION(BlueprintCallable)
	TArray<AMapUnit*> GetRowUnitInstance(int32 row, int32 col);

	// 查询格子的单行实例：输入row、col ； 返回TArray<AMapUnit*>
	UFUNCTION(BlueprintCallable)
	TArray<AMapUnit*> GetColumnUnitInstance(int32 row, int32 col);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 棋盘的二维数组
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<AMapUnit*> ChessboardGrid;

	// 棋盘的大小
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 BoardSize;

	// 获取一维数组中的索引
	int32 GetIndex(int32 Row, int32 Column) const;
	

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
