// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridCounter.h"
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

    //——————————————————————————————初始化——————————————————————————————
	// 创建棋盘函数
	UFUNCTION(BlueprintCallable)
	void CreateChessboard(int32 Size);

	UFUNCTION(BlueprintCallable)
	void CreateGridCounter();
	//—————————————————————————————————————————————————————————————————
    
	

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

	// 查询格子的单列实例：输入row、col ； 返回TArray<AMapUnit*>
	UFUNCTION(BlueprintCallable)
	TArray<AMapUnit*> GetColumnUnitInstance(int32 row, int32 col);

	//————————————————————————————————————————————————————————————————————


	//——————————————————————————————修改格子数——————————————————————————————

	// 加减运算: 输入AmapUnit*格子实例、int32 AddNum（正负数） ； 自动更新计数器
	UFUNCTION(BlueprintCallable)
	void AddUnitNum(AMapUnit* UnitInstance, int32 AddNum);

	// 清空运算: 输入AmapUnit*格子实例 ； 该格UnitNum清零
	UFUNCTION(BlueprintCallable)
	void ClearUnitNum(AMapUnit* UnitInstance);
	
	//————————————————————————————————————————————————————————————————————
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 棋盘的一维数组
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<AMapUnit*> ChessboardGrid;

	// 格子累加器数组
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<AGridCounter*> GridCounters;
	
	// 棋盘的大小
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 BoardSize;

	// 获取一维数组中的索引
	int32 GetIndex(int32 Row, int32 Column) const;
	

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
