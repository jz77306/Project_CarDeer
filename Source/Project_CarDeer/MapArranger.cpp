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

