// Fill out your copyright notice in the Description page of Project Settings.


#include "MapUnit.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMapUnit::AMapUnit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//初始化随机数
	InitRandUnitNum();

	
}

void AMapUnit::InitRandUnitNum()
{
	UnitNum = UKismetMathLibrary::RandomIntegerInRange(-2,2);
}

void AMapUnit::SetIndices(int32 NewRowIndex, int32 NewColumnIndex)
{
	// 设置格子的行列索引
	RowIndex = NewRowIndex;
	ColumnIndex = NewColumnIndex;
}

void AMapUnit::SetUnitNum(int32 NewUnitNum)
{
	// 设置格子的数字
	UnitNum = NewUnitNum;
}




// Called when the game starts or when spawned
void AMapUnit::BeginPlay()
{
	Super::BeginPlay();

	UpdateUnitNumShow();
}

// Called every frame
void AMapUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

