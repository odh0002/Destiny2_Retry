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
	case 1: // ���������� �̵��ϰ� �ϴ� 
		//�̰� �÷��̾ �������� ���������� ���׶��� ȸ���ϴ� ��
		//SetActorLocation(GetActorLocation() + GetActorRightVector() * MoveSpeed * DeltaTime);
		SetActorLocation(GetActorLocation() + Dir * MoveSpeed * DeltaTime);
		break;
	case 2: //�������� �̵��ϰ� �ϴ�
		//�̰� �÷��̾ �������� �������� ���׶��� ȸ���ϴ� ��
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
		//������ ��ġ�� �Ѿ� ����
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
		//���������θ� �̵��ϰ� ����� ���� ������ ���⼭ ������
		Dir = GetActorRightVector();
		//�ش� �׼��� �����϶�� ���ڸ� ������
		ActionNum = 1;
		//������ ��ġ�� �Ѿ� ����
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
		//���������θ� �̵��ϰ� ����� ���� ������ ���⼭ ������
		Dir = -(GetActorRightVector());
		//�ش� �׼��� �����϶�� ���ڸ� ������
		ActionNum = 2;
		//������ ��ġ�� �Ѿ� ����
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
		//������ ��ġ�� �Ѿ� ����
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

