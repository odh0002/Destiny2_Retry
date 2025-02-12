// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyAIController.h"
#include "EnemySpawner.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	//Base Speed And Health Setting
	Health = 100.0f;
	MaxHealth = Health;
	MoveSpeed = 300.0f;
	//AttackRange = 150.0f;
	//ChaseRange = 100.0f;
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;

	//EnemySpawner���� �Լ��� EnemySpawer�� ���� ������ �ȵǾ ������ �� ������ �ִ� EnemySpawner�� ������ ã�� �����صд�.
	EnemySpawner = Cast<AEnemySpawner>(UGameplayStatics::GetActorOfClass(GetWorld(), AEnemySpawner::StaticClass()));
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyBase::GetDamage(float DamageAmount)
{
	Health -= DamageAmount;
	// Dead Event
	if (Health <= 0)
	{
		Die();
	}
}

void AEnemyBase::Die()
{
	//AODHTestGameMode* GameMode = Cast<AODHTestGameMode>(GetWorld()->GetAuthGameMode());
	/*if (GameMode)
	{
		GameMode->PlusEnemyDeadCount();
	}
	*/

	////���̽��� ������ ���� ����ϴ� ���� �ٸ��� ó������
	//switch (mWaveState)
	//{
	//case EEnemyWaveState::WaveA: //���̺� A�� ���� ���
	//	//�����ʿ��� �Ҽ� ���̺�� ��� �ҽ��� ����
	//	EnemySpawner->WaveEnemyCountDown(1);
	//	//���ó���� ����
	//	SetLifeSpan(3.0f);
	//	break;
	//
	//case EEnemyWaveState::WaveB:
	//	//�����ʿ��� �Ҽ� ���̺�� ��� �ҽ��� ����
	//	EnemySpawner->WaveEnemyCountDown(2);
	//	//���ó���� ����
	//	SetLifeSpan(3.0f);
	//	break;
	//
	//case EEnemyWaveState::WaveC:
	//	//�����ʿ��� �Ҽ� ���̺�� ��� �ҽ��� ����
	//	EnemySpawner->WaveEnemyCountDown(3);
	//	//���ó���� ����
	//	SetLifeSpan(3.0f);
	//	break;
	//
	//case EEnemyWaveState::NoWave: //���̺꿡 ������ ���� ���
	//	//�׳� ��� ó���� ����
	//	SetLifeSpan(3.0f);
	//	break;
	//default:
	//	break;
	//}

	//���̽��� ������ ���� ����ϴ� ���� �ٸ��� ó������
	switch (SetWave)
	{
	case 1: //���̺� A�� ���� ���
		//�����ʿ��� �Ҽ� ���̺�� ��� �ҽ��� ����
		EnemySpawner->WaveEnemyCountDown(1);
		//���ó���� ����
		SetLifeSpan(3.0f);
		break;

	case 2:
		//�����ʿ��� �Ҽ� ���̺�� ��� �ҽ��� ����
		EnemySpawner->WaveEnemyCountDown(2);
		//���ó���� ����
		SetLifeSpan(3.0f);
		break;

	case 3:
		//�����ʿ��� �Ҽ� ���̺�� ��� �ҽ��� ����
		EnemySpawner->WaveEnemyCountDown(3);
		//���ó���� ����
		SetLifeSpan(3.0f);
		break;

	case 4: //���̺꿡 ������ ���� ���
		//�׳� ��� ó���� ����
		SetLifeSpan(3.0f);
		break;
	default:
		break;
	}


}

//void AEnemyBase::SetWaveA(AEnemySpawner* Spawner)
//{
//	//���ʹ̰� ��� ���̺꿡 ���ϴ��� ������ ����
//	//mWaveState = EEnemyWaveState::WaveA;
//
//	SetWave = 1;
//
//	//�����ʿ��� ������ �˷��ֱ� ���� ������ ������ �����ص�
//	EnemySpawner = Spawner;
//}

void AEnemyBase::SetWaveA()
{
	SetWave = 1;
}

//void AEnemyBase::SetWaveB(AEnemySpawner* Spawner)
//{
//	//���ʹ̰� ��� ���̺꿡 ���ϴ��� ������ ����
//	//mWaveState = EEnemyWaveState::WaveB;
//
//	SetWave = 2;
//
//	//�����ʿ��� ������ �˷��ֱ� ���� ������ ������ �����ص�
//	EnemySpawner = Spawner;
//}

void AEnemyBase::SetWaveB()
{
	SetWave = 2;
}

//void AEnemyBase::SetWaveC(AEnemySpawner* Spawner)
//{
//	//���ʹ̰� ��� ���̺꿡 ���ϴ��� ������ ����
//	//mWaveState = EEnemyWaveState::WaveC;
//
//	SetWave = 3;
//
//	//�����ʿ��� ������ �˷��ֱ� ���� ������ ������ �����ص�
//	EnemySpawner = Spawner;
//}

void AEnemyBase::SetWaveC()
{
	SetWave = 3;
}

