// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyAIController.h"
#include "EnemySpawner.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHPWidget.h"

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

	EnemyOwner = this;

	//Base Speed And Health Setting
	//Health = 100.0f;
	//MaxHealth = Health;
	//MoveSpeed = 300.0f;
	//AttackRange = 150.0f;
	//ChaseRange = 100.0f;
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;

	//EnemySpawner에서 함수로 EnemySpawer의 정보 전달이 안되어서 생성될 때 레벨에 있는 EnemySpawner의 정보를 찾아 저장해둔다.
	EnemySpawner = Cast<AEnemySpawner>(UGameplayStatics::GetActorOfClass(GetWorld(), AEnemySpawner::StaticClass()));

	EnemyUI = CreateWidget<UEnemyHPWidget>(GetWorld(), EnemyWidget);

	if (EnemyUI)
	{
		EnemyUI->AddToViewport();
	}
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
	else{}
}

void AEnemyBase::Die()
{
	//케이스를 나눠서 각각 사망하는 것을 다르게 처리해줌
	switch (SetWave)
	{
	case 1: //웨이브 A에 속할 경우
		//스포너에게 소속 웨이브와 사망 소식을 전달
		EnemySpawner->WaveEnemyCountDown(SetWave);
		//사망처리를 해줌
		SetLifeSpan(3.0f);
		break;

	case 2:
		//스포너에게 소속 웨이브와 사망 소식을 전달
		EnemySpawner->WaveEnemyCountDown(SetWave);
		//사망처리를 해줌
		SetLifeSpan(3.0f);
		break;

	case 3:
		//스포너에게 소속 웨이브와 사망 소식을 전달
		EnemySpawner->WaveEnemyCountDown(SetWave);
		//사망처리를 해줌
		SetLifeSpan(3.0f);
		break;

	case 4: //웨이브에 속하지 않을 경우
		//그냥 사망 처리를 해줌
		SetLifeSpan(3.0f);
		break;
	default:
		break;
	}


}

void AEnemyBase::SetWaveA()
{
	SetWave = 1;
}

void AEnemyBase::SetWaveB()
{
	SetWave = 2;
}

void AEnemyBase::SetWaveC()
{
	SetWave = 3;
}

