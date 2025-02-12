// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//플레이어가 들어왔다는 정보를 얻으면
	if (Fight && bWaveA == false)
	{
		bWaveA = true;
		//웨이브 A를 소환하게 만듦
		SpawnEnemyWave(WaveA, 1);
	}

	//웨이브 A의 적이 다 잡히거나 조건을 달성하면
	if (WaveAClera && !bWaveB)
	{
		bWaveB = true;
		//웨이브 B를 소환하게 만듦
		SpawnEnemyWave(WaveB, 2);
	}

	//웨이브 B의 적이 다 잡히거나 조건을 달성하면
	if (WaveBClera && !bWaveC)
	{
		bWaveC = true;
		//웨이브 C를 소환하게 만듦
		SpawnEnemyWave(WaveC, 3);
	}

	//웨이브 C의 적이 다 잡히거나 조건을 달성하면
	if (WaveCClera)
	{
		//게임 클리어?
	}
}

void AEnemySpawner::SpawnEnemyWave(TArray<TSubclassOf<AEnemyBase>> Wave, int32 WaveNum)
{
	//한 웨이브의 총 몬스터 수를 계산해서 그 만큼 반복문이 돌아감
	for (int i = 0; i < Wave.Num(); ++i)
	{
		//반복으로 해당 웨이브안에 적들이 소환 >> 딜레이가 없기에 아마 한꺼번에 소환이 될 같음
		GetWorld()->SpawnActor<AEnemyBase>(Wave[i], FTransform(FVector(0)));

		//if (WaveNum == 1)
		//{
		//	//해당 웨이브 카운트를 1 증가
		//	WaveAEnemys += 1;
		//	//해당 적에게 자신이 어느 웨이브에 속하고 스포너 정보를 알려줌 
		//	//Cast<AEnemyBase>(Wave[i])->SetWaveA(this);
		//	Cast<AEnemyBase>(Wave[i])->SetWaveA();
		//}
		//else if (WaveNum == 2)
		//{
		//	//해당 웨이브 카운트를 1 증가
		//	WaveBEnemys += 1;
		//	//해당 적에게 자신이 어느 웨이브에 속하고 스포너 정보를 알려줌
		//	//Cast<AEnemyBase>(Wave[i])->SetWaveA(this);
		//	Cast<AEnemyBase>(Wave[i])->SetWaveB();
		//}
		//else if (WaveNum == 3)
		//{
		//	//해당 웨이브 카운트를 1 증가
		//	WaveCEnemys += 1;
		//	//해당 적에게 자신이 어느 웨이브에 속하고 스포너 정보를 알려줌
		//	//Cast<AEnemyBase>(Wave[i])->SetWaveA(this);
		//	Cast<AEnemyBase>(Wave[i])->SetWaveC();
		//}
		//else {}

		//switch (WaveNum)
		//{
		//case 1:	//WaveA에 속함
		//	//해당 웨이브 카운트를 1 증가
		//	WaveAEnemys += 1;
		//	//해당 적에게 자신이 어느 웨이브에 속하고 스포너 정보를 알려줌 
		//	//Cast<AEnemyBase>(Wave[i])->SetWaveA(this);
		//	Cast<AEnemyBase>(Wave[i])->SetWaveA();
		//	break;
		//case 2:	//WaveB에 속함
		//	//해당 웨이브 카운트를 1 증가
		//	WaveBEnemys += 1;
		//	//해당 적에게 자신이 어느 웨이브에 속하고 스포너 정보를 알려줌 
		//	//Cast<AEnemyBase>(Wave[i])->SetWaveA(this);
		//	Cast<AEnemyBase>(Wave[i])->SetWaveB();
		//	break;
		//case 3:	//WaveC에 속함
		//	//해당 웨이브 카운트를 1 증가
		//	WaveCEnemys += 1;
		//	//해당 적에게 자신이 어느 웨이브에 속하고 스포너 정보를 알려줌 
		//	//Cast<AEnemyBase>(Wave[i])->SetWaveA(this);
		//	Cast<AEnemyBase>(Wave[i])->SetWaveC();
		//	break;
		//case 4:	//wave에 속하지 않을 경우 아무런 처리가 없음
		//	break;
		//default:
		//	break;
		//}
	}
}

void AEnemySpawner::WaveEnemyCountDown(int32 WaveNum)
{
	switch (WaveNum)
	{
	case 1:	//WaveA에 속함

		//카운트를 하나 줄임
		WaveAEnemys -= 1;

		//일정 수량 이하일 경우
		if (WaveAEnemys < 3)
		{
			//다음 웨이브를 소환
			WaveAClera = true;
		}
		break;
	case 2:	//WaveB에 속함

		//카운트를 하나 줄임
		WaveBEnemys -= 1;

		//일정 수량 이하일 경우
		if (WaveBEnemys < 3)
		{
			//다음 웨이브를 소환
			WaveBClera = true;
		}

		break;
	case 3:	//WaveC에 속함

		//카운트를 하나 줄임
		WaveCEnemys -= 1;

		//일정 수량 이하일 경우
		if (WaveCEnemys == 0)
		{
			//다음 웨이브를 소환
			WaveCClera = true;
		}

		break;
	case 4:	//wave에 속하지 않을 경우 아무런 후처리가 없음
		break;
	default:
		break;
	}
}
