// Fill out your copyright notice in the Description page of Project Settings.


#include "GridCounter.h"
#include "MapArranger.h"

// Sets default values
AGridCounter::AGridCounter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RowColMark = ERowColumnMark::EC_Defult;
}


void AGridCounter::SetRowColMark(ERowColumnMark NewMark)
{
	RowColMark = NewMark;
}

void AGridCounter::SetMapArranger(AMapArranger* MapArrangerInst)
{
	MapArranger = MapArrangerInst;
}

void AGridCounter::SetRowColIndex(int32 NewIndex)
{
	RowColIndex = NewIndex;	
}

// Called when the game starts or when spawned
void AGridCounter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGridCounter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AGridCounter::UpdateCountersNum()
{
	int32 Sum=0;
	TArray<AMapUnit*> UnitInstances;
	if(RowColMark == ERowColumnMark::EC_Row)
	{
		UnitInstances = MapArranger->GetRowUnitInstance(RowColIndex,0);
	}
	else if(RowColMark == ERowColumnMark::EC_Column)
	{
		UnitInstances = MapArranger->GetColumnUnitInstance(0,RowColIndex);
	}
	for (auto UnitInstance : UnitInstances)
	{
		Sum += UnitInstance->GetUnitNum();
	}
	SumNum = Sum;
	//调用蓝图视效
	UpdateCountersNumShow();
}


