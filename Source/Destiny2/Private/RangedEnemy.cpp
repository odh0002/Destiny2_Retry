// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "RangedEnemyAI.h"
#include "REAnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "../Destiny2Projectile.h"

// Sets default values
ARangedEnemy::ARangedEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = 150.0f;
	MaxHealth = Health;
	MoveSpeed = 1000.0f;
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	
	//ĸ���ݶ��̴��� �������� �������ش�.
	GetCapsuleComponent()->SetCollisionProfileName(FName("Enemy"));
	//ĸ���ݶ��̴��� �浹 �̺�Ʈ�� �������ش�.
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ARangedEnemy::OnEnemyOverlap);
	//ó������ �ִ� ĸ���ݶ��̴��� ũ�����?�������ش�
	GetCapsuleComponent()->SetCapsuleHalfHeight(111.267365f);
	GetCapsuleComponent()->SetCapsuleRadius(56.549107f);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonHowitzer/Characters/Heroes/Howitzer/Skins/Tier_2/Domed/Meshes/Howitzer_Domed.Howitzer_Domed'"));

	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);

		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -110.0f), FRotator(0.0f, -90.0f, 0.0f));
	}

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePos"));
	Arrow->SetupAttachment(GetMesh());
	//�߻� ��ġ�� ĳ���� Ư�� ���Ͽ� ��ġ�ϰ� ����
	Arrow->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("BreachMuzzle"));

	//���� �ݸ��� ���� �� ����
	WeakCollision = CreateDefaultSubobject<USphereComponent>(TEXT("WeakCollision"));
	//�޽� �Ʒ��� ����
	WeakCollision->SetupAttachment(GetMesh());
	//�ݸ����� ĳ������ ���� �κп� ����
	WeakCollision->SetRelativeLocation(FVector(-5.0, 40.0f, 150.0f));
	//Ÿ���� EnemyWeak�� �����Ͽ� �ش� �����¿� �°� �浹�ǰ� ����
	WeakCollision->SetCollisionProfileName(FName("EnemyWeak"));
	//�浹�� ���?�Լ� ȣ��
	WeakCollision->OnComponentBeginOverlap.AddDynamic(this, &ARangedEnemy::OnWeakOverlap);
}

// Called when the game starts or when spawned
void ARangedEnemy::BeginPlay()
{
	Super::BeginPlay();

	AIController = Cast<ARangedEnemyAI>(GetController());

	EnemyType = 1;
}

// Called every frame
void ARangedEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Health <= 0)
	{
		AIController->Anim->bIsDead = true;
	}
	else
	{ 
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
		PlayAnimMontage(AIController->Anim->REMontage, 1.0f, FName("Fire"));
		//������ ��ġ�� �Ѿ� ����
		GetWorld()->SpawnActor<AEnemyBullet>(Bullet, Arrow->GetComponentTransform());
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

void ARangedEnemy::OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADestiny2Projectile* bullet = Cast<ADestiny2Projectile>(OtherActor);

	//�Ѿ��� ���� ���?
	if (bullet)
	{
		//�θ� Ŭ������ �ִ� �Լ��� �ҷ� ü���� ���ҽ�Ŵ
		GetDamage(15.0f);

		//�Ѿ��� �ı�
		bullet->Destroy();
	}
}

void ARangedEnemy::OnWeakOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADestiny2Projectile* bullet = Cast<ADestiny2Projectile>(OtherActor);

	//�Ѿ��� ���� ���?
	if (bullet)
	{
		//�θ� Ŭ������ �ִ� �Լ��� �ҷ� ü���� ���ҽ�Ŵ
		GetDamage(30.0f);

		//�Ѿ��� �ı�
		bullet->Destroy();
	}
}

