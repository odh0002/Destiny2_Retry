// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "RangedEnemyAI.h"

// Sets default values
ARangedEnemy::ARangedEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = 150.0f;
	MaxHealth = Health;
	MoveSpeed = 1000.0f;
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePos"));
	Arrow->SetupAttachment(RootComponent);
	Arrow->SetRelativeLocation(FVector(30.0f, 0.0f, 10.0f));
}

// Called when the game starts or when spawned
void ARangedEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARangedEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (ActionNum)
	{
	case 1: // 오른쪽으로 이동하게 하는 
		//이건 플레이어를 기준으로 오른쪽으로 동그랗게 회전하는 것
		//SetActorLocation(GetActorLocation() + GetActorRightVector() * MoveSpeed * DeltaTime);
		SetActorLocation(GetActorLocation() + Dir * MoveSpeed * DeltaTime);
		break;
	case 2: //왼쪽으로 이동하게 하는
		//이건 플레이어를 기준으로 왼쪽으로 동그랗게 회전하는 것
		//SetActorLocation(GetActorLocation() + -(GetActorRightVector()) * MoveSpeed * DeltaTime);
		SetActorLocation(GetActorLocation() + Dir * MoveSpeed * DeltaTime);
		break;
	default:
		break;
	}

	if (atkTime > 0)
	{
		atkTime -= DeltaTime;
	}
	else { return; }
}

// Called to bind functionality to input
void ARangedEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARangedEnemy::Attack()
{
	if (atkTime <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ranged Enemy Attack"));
		//정해진 위치에 총알 생성
		GetWorld()->SpawnActor<AEnemyBullet>(Bullet, Arrow->GetComponentTransform());
		atkTime = 2.0f;
	}
	else { return; }
}


void ARangedEnemy::RightMove()
{
	if (atkTime <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ranged Enemy Right Move"));
		//오른쪽으로만 이동하게 만들기 위해 방향을 여기서 지정함
		Dir = GetActorRightVector();
		//해당 액션을 실행하라고 숫자를 지정함
		ActionNum = 1;
		//정해진 위치에 총알 생성
		//GetWorld()->SpawnActor<AEnemyBullet>(Bullet, Arrow->GetComponentTransform());
		Attack();
		atkTime = 2.0f;
	}
	else { return; }
}

void ARangedEnemy::LeftMove()
{
	if (atkTime <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ranged Enemy Left Move"));
		//오른쪽으로만 이동하게 만들기 위해 방향을 여기서 지정함
		Dir = -(GetActorRightVector());
		//해당 액션을 실행하라고 숫자를 지정함
		ActionNum = 2;
		//정해진 위치에 총알 생성
		//GetWorld()->SpawnActor<AEnemyBullet>(Bullet, Arrow->GetComponentTransform());
		Attack();
		atkTime = 2.0f;
	}
	else { return; }
}

void ARangedEnemy::Stand()
{
	if (atkTime <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ranged Enemy Stand"));
		//정해진 위치에 총알 생성
		//GetWorld()->SpawnActor<AEnemyBullet>(Bullet, Arrow->GetComponentTransform());
		Attack();
		atkTime = 2.0f;
	}
	else { return; }
}

void ARangedEnemy::ActionNumReset()
{
	ActionNum = 0;
}

