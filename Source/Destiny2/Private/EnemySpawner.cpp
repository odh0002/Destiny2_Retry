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
		GetWorld()->SpawnActor<AEnemyBase>(Wave[i], FTransform(FVector(0)));

		//if (WaveNum == 1)
		//{
		//	//�ش� ���̺� ī��Ʈ�� 1 ����
		//	WaveAEnemys += 1;
		//	//�ش� ������ �ڽ��� ��� ���̺꿡 ���ϰ� ������ ������ �˷��� 
		//	//Cast<AEnemyBase>(Wave[i])->SetWaveA(this);
		//	Cast<AEnemyBase>(Wave[i])->SetWaveA();
		//}
		//else if (WaveNum == 2)
		//{
		//	//�ش� ���̺� ī��Ʈ�� 1 ����
		//	WaveBEnemys += 1;
		//	//�ش� ������ �ڽ��� ��� ���̺꿡 ���ϰ� ������ ������ �˷���
		//	//Cast<AEnemyBase>(Wave[i])->SetWaveA(this);
		//	Cast<AEnemyBase>(Wave[i])->SetWaveB();
		//}
		//else if (WaveNum == 3)
		//{
		//	//�ش� ���̺� ī��Ʈ�� 1 ����
		//	WaveCEnemys += 1;
		//	//�ش� ������ �ڽ��� ��� ���̺꿡 ���ϰ� ������ ������ �˷���
		//	//Cast<AEnemyBase>(Wave[i])->SetWaveA(this);
		//	Cast<AEnemyBase>(Wave[i])->SetWaveC();
		//}
		//else {}

		//switch (WaveNum)
		//{
		//case 1:	//WaveA�� ����
		//	//�ش� ���̺� ī��Ʈ�� 1 ����
		//	WaveAEnemys += 1;
		//	//�ش� ������ �ڽ��� ��� ���̺꿡 ���ϰ� ������ ������ �˷��� 
		//	//Cast<AEnemyBase>(Wave[i])->SetWaveA(this);
		//	Cast<AEnemyBase>(Wave[i])->SetWaveA();
		//	break;
		//case 2:	//WaveB�� ����
		//	//�ش� ���̺� ī��Ʈ�� 1 ����
		//	WaveBEnemys += 1;
		//	//�ش� ������ �ڽ��� ��� ���̺꿡 ���ϰ� ������ ������ �˷��� 
		//	//Cast<AEnemyBase>(Wave[i])->SetWaveA(this);
		//	Cast<AEnemyBase>(Wave[i])->SetWaveB();
		//	break;
		//case 3:	//WaveC�� ����
		//	//�ش� ���̺� ī��Ʈ�� 1 ����
		//	WaveCEnemys += 1;
		//	//�ش� ������ �ڽ��� ��� ���̺꿡 ���ϰ� ������ ������ �˷��� 
		//	//Cast<AEnemyBase>(Wave[i])->SetWaveA(this);
		//	Cast<AEnemyBase>(Wave[i])->SetWaveC();
		//	break;
		//case 4:	//wave�� ������ ���� ��� �ƹ��� ó���� ����
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
