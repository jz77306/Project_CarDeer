// Fill out your copyright notice in the Description page of Project Settings.


#include "MapArranger.h"

// Sets default values
AMapArranger::AMapArranger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//初始化默认值
	BoardSize = 0;
}

void AMapArranger::CreateChessboard(int32 Size)
{
	// 设置棋盘大小
	BoardSize = Size;

	// 清空棋盘数组
	ChessboardGrid.Empty();

	// 创建棋盘格子
	for (int32 Row = 0; Row < BoardSize; ++Row)
	{
		for (int32 Column = 0; Column < BoardSize; ++Column)
		{
			// 创建棋盘格子并添加到数组中
			UClass* AClass = LoadClass<AActor>(NULL,TEXT("/Game/Blueprints/BlockMap/BP_MapUnit.BP_MapUnit_C"));
			
			// 计算格子位置
			FVector Location = FVector(GetActorLocation().X - Row * 200.0f, GetActorLocation().Y + Column * 200.0f, 0.0f);

			// 创建棋盘格子并添加到数组中
			AMapUnit* NewMapUnit = GetWorld()->SpawnActor<AMapUnit>(AClass,Location, FRotator::ZeroRotator);
			
			if (NewMapUnit)
			{
				// 设置格子的行列索引
				NewMapUnit->SetIndices(Row, Column);

				// 将棋盘格子添加到数组中
				ChessboardGrid.Add(NewMapUnit);
			}
		}
	}
}

void AMapArranger::CreateGridCounter()
{
	// 清空累加器数组
	GridCounters.Empty();

	TArray<AMapUnit*> RowUnitInstance,ColumnUnitInstance;
	RowUnitInstance = GetRowUnitInstance(BoardSize-1,0);
	ColumnUnitInstance = GetColumnUnitInstance(0,BoardSize-1);

	// 添加行计数器
	for(auto i=0;i<BoardSize;i++)
	{
		//拿蓝图路径
		UClass* AClass = LoadClass<AActor>(NULL,TEXT("/Game/Blueprints/BlockMap/BP_GridCounter.BP_GridCounter_C"));
		//拿到当前边缘格实例位置
		FVector EdgeUnitLocation = ColumnUnitInstance[i]->GetActorLocation();
		//Spawn
		AGridCounter* GridCounterInstance = GetWorld()->SpawnActor<AGridCounter>(AClass,FVector(EdgeUnitLocation.X,EdgeUnitLocation.Y+200,0.0f),FRotator::ZeroRotator);
		//标注行
		GridCounterInstance->SetRowColMark(ERowColumnMark::EC_Row);
		//回传self引用
		GridCounterInstance->SetMapArranger(this);
		//回传第几行
		GridCounterInstance->SetRowColIndex(i);
		
		GridCounters.Add(GridCounterInstance);
	}
	// 添加列计数器
	for (auto i=0;i<BoardSize;i++)
	{
		//拿蓝图路径
		UClass* AClass = LoadClass<AActor>(NULL,TEXT("/Game/Blueprints/BlockMap/BP_GridCounter.BP_GridCounter_C"));
		//拿到当前边缘格实例位置
		FVector EdgeUnitLocation = RowUnitInstance[i]->GetActorLocation();
		//Spawn
		AGridCounter* GridCounterInstance = GetWorld()->SpawnActor<AGridCounter>(AClass,FVector(EdgeUnitLocation.X-200,EdgeUnitLocation.Y,0.0f),FRotator::ZeroRotator);
		//标记列
		GridCounterInstance->SetRowColMark(ERowColumnMark::EC_Column);
		//回传self引用
		GridCounterInstance->SetMapArranger(this);
		//回传第几列
		GridCounterInstance->SetRowColIndex(i);
		GridCounters.Add(GridCounterInstance);
	}
	
}

FVector AMapArranger::GetMapUnitLoc(int32 row, int32 col)
{
	// 查询格子的位置，返回FVector
	if (row >= 0 && row < BoardSize && col >= 0 && col < BoardSize)
	{
		int32 Index = GetIndex(row, col);
		if (Index != -1)
		{
			return ChessboardGrid[Index]->GetActorLocation();
		}
	}
	return FVector::ZeroVector;
}

AMapUnit* AMapArranger::GetMapUnitInstance(int32 row, int32 col)
{
	// 查询格子的实例：返回AMapUnit
	if (row >= 0 && row < BoardSize && col >= 0 && col < BoardSize)
	{
		int32 Index = GetIndex(row, col);
		if (Index != -1)
		{
			return ChessboardGrid[Index];
		}
	}
	return nullptr;
}

TArray<AMapUnit*> AMapArranger::GetRowUnitInstance(int32 row, int32 col)
{
	if (row >= 0 && row < BoardSize && col >= 0 && col < BoardSize)
	{
		TArray<AMapUnit*> UnitRowInstance;
		int32 Index = row*BoardSize;
		if(Index != -1)
		{
			for(auto i =Index;i<Index+BoardSize;i++)
			{
				UnitRowInstance.Add(ChessboardGrid[i]);
			}
			return UnitRowInstance;
		}
	}
	return TArray<AMapUnit*>();
}

TArray<AMapUnit*> AMapArranger::GetColumnUnitInstance(int32 row, int32 col)
{
	if (row >= 0 && row < BoardSize && col >= 0 && col < BoardSize)
	{
		TArray<AMapUnit*> UnitRowInstance;
		int32 Index = col % BoardSize;
		if(Index != -1)
		{
			for (auto i = Index;i<Index+5*BoardSize;i+=BoardSize)
			{
				UnitRowInstance.Add(ChessboardGrid[i]);
			}
			return UnitRowInstance;
		}
	}
	return TArray<AMapUnit*>();
}

TArray<AMapUnit*> AMapArranger::GetRowColumnIntersection()
{
	TArray<AMapUnit*> ColumnRowIntersectionArr;
	for(auto RowIndex=0;RowIndex<BoardSize;RowIndex++)
	{
		for (auto ColIndex = BoardSize;ColIndex<BoardSize*2;ColIndex++)
		{
			 if(GridCounters[ColIndex]->GetSumNum()==GridCounters[RowIndex]->GetSumNum() && GridCounters[ColIndex]->GetSumNum()!=0)
			 {
			 	AMapUnit* UnitInstance = GetMapUnitInstance(GridCounters[RowIndex]->GetRowColIndex(),GridCounters[ColIndex]->GetRowColIndex());
			 	ColumnRowIntersectionArr.Add(UnitInstance);
			 }
		}
	}
	
	return ColumnRowIntersectionArr;
}

TArray<AMapUnit*> AMapArranger::GetTotalRowColUnitInstance(int32 row, int32 col)
{
	TArray<AMapUnit*> RowUnitInstance= GetRowUnitInstance(row,col),ColUnitInstance= GetColumnUnitInstance(row,col);
	//TArray<AMapUnit*> TotalRowColUnitInstance;
	TSet<AMapUnit*> UniqueTotalRowColUnitInstance;
	TArray<AMapUnit*> FinalTotalRowColUnitInstance;
	UniqueTotalRowColUnitInstance.Append(RowUnitInstance);
	UniqueTotalRowColUnitInstance.Append(ColUnitInstance);

	for(AMapUnit* UnitInstance : UniqueTotalRowColUnitInstance)
	{
		FinalTotalRowColUnitInstance.Add(UnitInstance);
	}
	
	return FinalTotalRowColUnitInstance; 
	
}

void AMapArranger::AddUnitNum(AMapUnit* UnitInstance, int32 AddNum)
{
	int32 NewUnitNum = UnitInstance->GetUnitNum()+ AddNum;
	if(NewUnitNum>2)
	{
		UnitInstance->SetUnitNum(2);
	}
	else if(NewUnitNum<-2)
	{
		UnitInstance->SetUnitNum(-2);
	}
	else
	{
		UnitInstance->SetUnitNum(NewUnitNum);
	}

	//更新格子视效
	UnitInstance->UpdateUnitNumShow();
	
	//更新计数器
	int32 currentRow = UnitInstance->GetRowIndex();
	int32 currentColumn = UnitInstance->GetColumnIndex();

	GridCounters[currentRow]->UpdateCountersNum();
	GridCounters[currentColumn+BoardSize]->UpdateCountersNum();
}

void AMapArranger::ClearUnitNum(AMapUnit* UnitInstance)
{
	UnitInstance->SetUnitNum(0);

	//更新格子视效
	UnitInstance->UpdateUnitNumShow();
	
	//更新计数器
	int32 currentRow = UnitInstance->GetRowIndex();
	int32 currentColumn = UnitInstance->GetColumnIndex();

	GridCounters[currentRow]->UpdateCountersNum();
	GridCounters[currentColumn+BoardSize]->UpdateCountersNum();
}

// Called when the game starts or when spawned
void AMapArranger::BeginPlay()
{
	Super::BeginPlay();
	
}

int32 AMapArranger::GetIndex(int32 Row, int32 Column) const
{
	// 获取一维数组中的索引
	return Row * BoardSize + Column;
}

// Called every frame
void AMapArranger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

