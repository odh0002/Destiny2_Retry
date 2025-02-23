// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Destiny2Character.h"
#include "Components/SphereComponent.h"
#include "../Destiny2Projectile.h"
#include "Components/CapsuleComponent.h"
#include "MEAnimInstance.h"
#include "Components/BoxComponent.h"

// Sets default values
AMeleeEnemy::AMeleeEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = 150.0f;
	MaxHealth = Health;
	MoveSpeed = 1000.0f;
	AttackRange = 300.0f;
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;

	//ĸ���ݶ��̴��� �������� �������ش�.
	GetCapsuleComponent()->SetCollisionProfileName(FName("Enemy"));
	//ĸ���ݶ��̴��� �浹 �̺�Ʈ�� �������ش�.
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMeleeEnemy::OnEnemyOverlap);
	//ó������ �ִ� ĸ���ݶ��̴��� ũ����� �������ش�
	GetCapsuleComponent()->SetCapsuleHalfHeight(113.558517f);
	GetCapsuleComponent()->SetCapsuleRadius(51.428543f);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGrux/Characters/Heroes/Grux/Skins/Tier_2/Grux_Beetle_Molten/Meshes/GruxMolten.GruxMolten'"));

	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);

		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -115.0f), FRotator(0.0f, -90.0f, 0.0f));
	}

	

	//���� �ݸ��� ���� �� ����
	HeadCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Head"));
	//�޽� �Ʒ��� ��������
	HeadCollision->SetupAttachment(GetMesh());
	//�ݸ����� ĳ������ ����, �Ӹ� �κп� �������ش�
	HeadCollision->SetRelativeLocation(FVector(-15.0f, 45.0f, 175.0f));
	//�浹�� EnemyWeak�� �����Ͽ� �ش� �����¿� �°� �浹�ǰ� ����
	HeadCollision->SetCollisionProfileName(FName("EnemyWeak"));
	//�浹�� ��� �Լ� ȣ��
	HeadCollision->OnComponentBeginOverlap.AddDynamic(this, &AMeleeEnemy::OnHeadOverlap);

	//�ִϸ��̼� �������Ʈ �Ҵ�
	ConstructorHelpers::FClassFinder<UAnimInstance> tmpAnim(TEXT("/Script/Engine.AnimBlueprint'/Game/ODH/Blueprint/Anim/ABP_MeleeEnemy.ABP_MeleeEnemy'"));
	if (tmpAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(tmpAnim.Class);
	}

	//���⿡ ���� �ݸ����� ���� �����Ѵ�
	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
	//���� �ݸ����� �޽��� ���δ�
	WeaponCollision->SetupAttachment(GetMesh());
	//�ݸ����� ������ �̸��� �̿��Ͽ� �ش� �κп� ���δ�.
	WeaponCollision->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("FX_Trail_R_01"));
	//�ݸ����� ��ġ�� ũ�⸦ �������ش�.
	WeaponCollision->SetRelativeLocation(FVector(0.0f, 0.0f, -65.0f));
	WeaponCollision->SetRelativeScale3D(FVector(1.0f, 1.0f, 2.0f));
	WeaponCollision->SetCollisionProfileName(FName("EnemyWeapon"));
	WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AMeleeEnemy::OnWeaponOverlap);
	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AMeleeEnemy::BeginPlay()
{
	Super::BeginPlay();

	EnemyType = 0;
	Anim = Cast<UMEAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called every frame
void AMeleeEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (atkTime > 0)
	{
		atkTime -= DeltaTime;
	}
	else {  }

	if (Health <= 0)
	{
		
		Anim->bIsDead = true;
	}
	else{}
}

void AMeleeEnemy::Attack()
{
	if (atkTime <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Melee Enemy Attack"));

		Anim->bIsAttack = true;

		atkTime = 2.0f;



		////WeaponCollision->SetCollisionEnabled(ECollisionEnabled::);

		////���� �������� ����(����) ��ġ ��������
		//FVector CurLocation = GetMesh()->GetSocketLocation(SoketName);

		////���� �������� ��ġ�� ������ �ʱ�ȭ
		//if (PreLocation.IsNearlyZero())
		//{
		//	PreLocation = CurLocation;
		//	return;
		//}

		//// ��ü�� ����Ʈ���̽��� �ɸ� ��� ������ ��� Hit����
		//FHitResult hitResult; 
		////�浹 ���� ���� �� �߰����� �ɼ��� ����
		//FCollisionQueryParams Params;
		////�ڱ��ڽ��� �����ϵ��� ����
		//Params.AddIgnoredActor(GetOwner());

		////����Ʈ���̽��� �׷��� �浹�� ��ü�� �ִ��� Ȯ���ϴ� ��
		////�浹�� ���� ��ġ, ������ ��ġ, ������ �浹�ϴ���, �ڼ��� ������ �������� ��ȣ�� ���´�.
		//bool bHit = GetWorld()->LineTraceSingleByChannel(hitResult, PreLocation, CurLocation, ECC_GameTraceChannel1, Params);

		////���� �ε��� ��ü�� �ִ� ���
		//if (bHit)
		//{
		//	AActor* HitActor = hitResult.GetActor();
		//	if (HitActor)
		//	{
		//		UE_LOG(LogTemp, Log, TEXT("Hit Actor: %s"), *HitActor->GetName());
		//	}
		//}

		//PreLocation = CurLocation;

	}
	else { return; }
}

void AMeleeEnemy::OnWeaponCollision()
{
	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AMeleeEnemy::OffWeaponCollision()
{
	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMeleeEnemy::OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADestiny2Projectile* bullet = Cast<ADestiny2Projectile>(OtherActor);

	//�Ѿ��� ���� ���
	if (bullet)
	{
		//�θ� Ŭ������ �ִ� �Լ��� �ҷ� ü���� ���ҽ�Ŵ
		GetDamage(15.0f);

		//�Ѿ��� �ı�
		bullet->Destroy();
	}
}

void AMeleeEnemy::OnHeadOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADestiny2Projectile* bullet = Cast<ADestiny2Projectile>(OtherActor);
	
	//�Ѿ��� ���� ���
	if (bullet)
	{
		//�θ� Ŭ������ �ִ� �Լ��� �ҷ� ü���� ���ҽ�Ŵ
		GetDamage(30.0f);

		//�Ѿ��� �ı�
		bullet->Destroy();
	}
}

void AMeleeEnemy::OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADestiny2Character* player = Cast<ADestiny2Character>(OtherActor);

	if (player)
	{
		UE_LOG(LogTemp, Warning, TEXT("Melee Enemy Attack -> Player"));
	}
}
