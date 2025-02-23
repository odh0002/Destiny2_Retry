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
	
	//Ä¸ï¿½ï¿½ï¿½Ý¶ï¿½ï¿½Ì´ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ø´ï¿½.
	GetCapsuleComponent()->SetCollisionProfileName(FName("Enemy"));
	//Ä¸ï¿½ï¿½ï¿½Ý¶ï¿½ï¿½Ì´ï¿½ï¿½ï¿½ ï¿½æµ¹ ï¿½Ìºï¿½Æ®ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ø´ï¿½.
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ARangedEnemy::OnEnemyOverlap);
	//Ã³ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ö´ï¿½ Ä¸ï¿½ï¿½ï¿½Ý¶ï¿½ï¿½Ì´ï¿½ï¿½ï¿½ Å©ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ø´ï¿½
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
	//ï¿½ß»ï¿½ ï¿½ï¿½Ä¡ï¿½ï¿½ Ä³ï¿½ï¿½ï¿½ï¿½ Æ¯ï¿½ï¿½ ï¿½ï¿½ï¿½Ï¿ï¿½ ï¿½ï¿½Ä¡ï¿½Ï°ï¿½ ï¿½ï¿½ï¿½ï¿½
	Arrow->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("BreachMuzzle"));

	//ï¿½ï¿½ï¿½ï¿½ ï¿½Ý¸ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
	WeakCollision = CreateDefaultSubobject<USphereComponent>(TEXT("WeakCollision"));
	//ï¿½Þ½ï¿½ ï¿½Æ·ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
	WeakCollision->SetupAttachment(GetMesh());
	//ï¿½Ý¸ï¿½ï¿½ï¿½ï¿½ï¿½ Ä³ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ÎºÐ¿ï¿½ ï¿½ï¿½ï¿½ï¿½
	WeakCollision->SetRelativeLocation(FVector(-5.0, 40.0f, 150.0f));
	//Å¸ï¿½ï¿½ï¿½ï¿½ EnemyWeakï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ï¿ï¿½ ï¿½Ø´ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Â¿ï¿½ ï¿½Â°ï¿½ ï¿½æµ¹ï¿½Ç°ï¿½ ï¿½ï¿½ï¿½ï¿½
	WeakCollision->SetCollisionProfileName(FName("EnemyWeak"));
	//ï¿½æµ¹ï¿½ï¿½ ï¿½ï¿½ï¿?ï¿½Ô¼ï¿½ È£ï¿½ï¿½
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
		case 1: // ¿À¸¥ÂÊÀ¸·Î ÀÌµ¿ÇÏ°Ô ÇÏ´Â 
			//ÀÌ°Ç ÇÃ·¹ÀÌ¾î¸¦ ±âÁØÀ¸·Î ¿À¸¥ÂÊÀ¸·Î µ¿±×¶þ°Ô È¸ÀüÇÏ´Â °Í
			//SetActorLocation(GetActorLocation() + GetActorRightVector() * MoveSpeed * DeltaTime);
			SetActorLocation(GetActorLocation() + Dir * MoveSpeed * DeltaTime);
			break;
		case 2: //¿ÞÂÊÀ¸·Î ÀÌµ¿ÇÏ°Ô ÇÏ´Â
			//ÀÌ°Ç ÇÃ·¹ÀÌ¾î¸¦ ±âÁØÀ¸·Î ¿ÞÂÊÀ¸·Î µ¿±×¶þ°Ô È¸ÀüÇÏ´Â °Í
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
		//Á¤ÇØÁø À§Ä¡¿¡ ÃÑ¾Ë »ý¼º
		GetWorld()->SpawnActor<AEnemyBullet>(Bullet, Arrow->GetComponentTransform());
	}
	else { return; }
}


void ARangedEnemy::RightMove()
{
	if (atkTime <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ranged Enemy Right Move"));
		//¿À¸¥ÂÊÀ¸·Î¸¸ ÀÌµ¿ÇÏ°Ô ¸¸µé±â À§ÇØ ¹æÇâÀ» ¿©±â¼­ ÁöÁ¤ÇÔ
		Dir = GetActorRightVector();
		//ÇØ´ç ¾×¼ÇÀ» ½ÇÇàÇÏ¶ó°í ¼ýÀÚ¸¦ ÁöÁ¤ÇÔ
		ActionNum = 1;
		//Á¤ÇØÁø À§Ä¡¿¡ ÃÑ¾Ë »ý¼º
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
		//¿À¸¥ÂÊÀ¸·Î¸¸ ÀÌµ¿ÇÏ°Ô ¸¸µé±â À§ÇØ ¹æÇâÀ» ¿©±â¼­ ÁöÁ¤ÇÔ
		Dir = -(GetActorRightVector());
		//ÇØ´ç ¾×¼ÇÀ» ½ÇÇàÇÏ¶ó°í ¼ýÀÚ¸¦ ÁöÁ¤ÇÔ
		ActionNum = 2;
		//Á¤ÇØÁø À§Ä¡¿¡ ÃÑ¾Ë »ý¼º
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
		//Á¤ÇØÁø À§Ä¡¿¡ ÃÑ¾Ë »ý¼º
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

	//ï¿½Ñ¾ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿?
	if (bullet)
	{
		//ï¿½Î¸ï¿½ Å¬ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ö´ï¿½ ï¿½Ô¼ï¿½ï¿½ï¿½ ï¿½Ò·ï¿½ Ã¼ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Ò½ï¿½Å´
		GetDamage(15.0f);

		//ï¿½Ñ¾ï¿½ï¿½ï¿½ ï¿½Ä±ï¿½
		bullet->Destroy();
	}
}

void ARangedEnemy::OnWeakOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADestiny2Projectile* bullet = Cast<ADestiny2Projectile>(OtherActor);

	//ï¿½Ñ¾ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿?
	if (bullet)
	{
		//ï¿½Î¸ï¿½ Å¬ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ö´ï¿½ ï¿½Ô¼ï¿½ï¿½ï¿½ ï¿½Ò·ï¿½ Ã¼ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Ò½ï¿½Å´
		GetDamage(30.0f);

		//ï¿½Ñ¾ï¿½ï¿½ï¿½ ï¿½Ä±ï¿½
		bullet->Destroy();
	}
}

