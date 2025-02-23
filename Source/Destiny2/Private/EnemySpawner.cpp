// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "EngineUtils.h"

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

	SetSpawnPoints();
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//�÷��̾ ���Դٴ� ������ ������
	if (Fight && bWaveA == false)
	{
		bWaveA = true;
		//���̺� A�� ��ȯ�ϰ� ����
		SpawnEnemyWave(WaveA, 1);
	}

	//���̺� A�� ���� �� �����ų� ������ �޼��ϸ�
	if (WaveAClera && !bWaveB)
	{
		bWaveB = true;
		//���̺� B�� ��ȯ�ϰ� ����
		SpawnEnemyWave(WaveB, 2);
	}

	//���̺� B�� ���� �� �����ų� ������ �޼��ϸ�
	if (WaveBClera && !bWaveC)
	{
		bWaveC = true;
		//���̺� C�� ��ȯ�ϰ� ����
		SpawnEnemyWave(WaveC, 3);
	}

	//���̺� C�� ���� �� �����ų� ������ �޼��ϸ�
	if (WaveCClera)
	{
		//���� Ŭ����?
	}
}

void AEnemySpawner::SpawnEnemyWave(TArray<TSubclassOf<AEnemyBase>> Wave, int32 WaveNum)
{
	//�� ���̺��� �� ���� ���� ����ؼ� �� ��ŭ �ݺ����� ���ư�
	for (int i = 0; i < Wave.Num(); ++i)
	{
		//�ݺ����� �ش� ���̺�ȿ� ������ ��ȯ >> �����̰� ���⿡ �Ƹ� �Ѳ����� ��ȯ�� �� ����
		//GetWorld()->SpawnActor<AEnemyBase>(Wave[i], FTransform(FVector(0)));

		AEnemyBase* spawnEnemy = GetWorld()->SpawnActor<AEnemyBase>(Wave[i], spawnPoints[i]->GetActorLocation(), FRotator(0));

		//

		switch (WaveNum)
		{
		case 1:
			WaveAEnemys += 1;
			//GetWorld()->GetTimerManager().SetTimer(MethodCalling, spawnEnemy, &AEnemyBase::SetWaveA, 0.2f, false);
			spawnEnemy->SetWaveA();
			break;
		case 2:
			WaveBEnemys += 1;
			//GetWorld()->GetTimerManager().SetTimer(MethodCalling, spawnEnemy, &AEnemyBase::SetWaveB, 0.2f, false);
			spawnEnemy->SetWaveB();
			break;
		case 3:
			WaveCEnemys += 1;
			//GetWorld()->GetTimerManager().SetTimer(MethodCalling, spawnEnemy, &AEnemyBase::SetWaveC, 0.2f, false);
			spawnEnemy->SetWaveC();
			break;
		case 4:
			break;
		default:
			break;
		}
	}
}

void AEnemySpawner::WaveEnemyCountDown(int32 WaveNum)
{
	switch (WaveNum)
	{
	case 1:	//WaveA�� ����

		//ī��Ʈ�� �ϳ� ����
		WaveAEnemys -= 1;

		//���� ���� ������ ���
		if (WaveAEnemys < 3)
		{
			//���� ���̺긦 ��ȯ
			WaveAClera = true;
		}
		break;
	case 2:	//WaveB�� ����

		//ī��Ʈ�� �ϳ� ����
		WaveBEnemys -= 1;

		//���� ���� ������ ���
		if (WaveBEnemys < 3)
		{
			//���� ���̺긦 ��ȯ
			WaveBClera = true;
		}

		break;
	case 3:	//WaveC�� ����

		//ī��Ʈ�� �ϳ� ����
		WaveCEnemys -= 1;

		//���� ���� ������ ���
		if (WaveCEnemys == 0)
		{
			//���� ���̺긦 ��ȯ
			WaveCClera = true;
		}

		break;
	case 4:	//wave�� ������ ���� ��� �ƹ��� ��ó���� ����
		break;
	default:
		break;
	}
}

void AEnemySpawner::SetSpawnPoints()
{
	for (TActorIterator<AActor> iter(GetWorld()); iter; ++iter)
	{
		AActor* spawn = *iter;
		if (spawn->GetName().Contains(TEXT("BP_EnemySpawnPoint")))
		{
			//�迭�� ���� ��Ҹ� �־���
			spawnPoints.Add(spawn);
		}
	}
}

int32 AEnemySpawner::RandomSpawnPoint()
{
	return FMath::RandRange(0, spawnPoints.Num()-1);
}

void AEnemySpawner::OnPlayer()
{
	Fight = true;
}
