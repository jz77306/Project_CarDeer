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
	void CreateChessboard(int32 Size);

	// 摆放棋子函数
	//void PlaceChessPiece(AChessPiece* ChessPiece, int32 Row, int32 Column);

	// 查询格子的位置，返回FVector
	UFUNCTION(BlueprintCallable)
	FVector FindMapUnitLoc(int32 row, int32 col);

	// 查询格子的实例：返回AMapUnit
	UFUNCTION(BlueprintCallable)
	AMapUnit* GetMapUnitInstance(int32 row, int32 col);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 棋盘的二维数组
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<TArray<AMapUnit*>> ChessboardGrid;

	// 棋盘的大小
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 BoardSize;
	

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
