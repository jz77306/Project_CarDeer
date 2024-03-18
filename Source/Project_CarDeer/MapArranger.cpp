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
		TArray<AMapUnit*> RowSquares;
		for (int32 Column = 0; Column < BoardSize; ++Column)
		{
			// 创建棋盘格子并添加到数组中
			UClass* AClass = LoadClass<AActor>(NULL,TEXT("/Game/Blueprints/BlockMap/BP_MapUnit.BP_MapUnit_C"));
			AMapUnit* NewSquare = GetWorld()->SpawnActor<AMapUnit>(AClass); 
			if (NewSquare)
			{
				// 设置格子的位置和索引
				NewSquare->SetActorLocation(FVector(GetActorLocation().X-Column * 200.0f, GetActorLocation().Y+Row * 200.0f, 0.0f));
				NewSquare->SetIndices(Row, Column);

				RowSquares.Add(NewSquare);
			}
		}
		ChessboardGrid.Add(RowSquares);
	}
}

// Called when the game starts or when spawned
void AMapArranger::BeginPlay()
{
	Super::BeginPlay();

	// 初始化棋盘格
	CreateChessboard(5);
}

// Called every frame
void AMapArranger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

