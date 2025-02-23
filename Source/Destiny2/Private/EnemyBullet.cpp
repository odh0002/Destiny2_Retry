// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBullet.h"
#include "../Destiny2Character.h"
#include "Components/SphereComponent.h"

// Sets default values
AEnemyBullet::AEnemyBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(Collision);
	Collision->SetSphereRadius(10.067607f);
	Collision->SetCollisionProfileName(FName("REBullet"));
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBullet::OnEnemyBulletOverlap);
}

// Called when the game starts or when spawned
void AEnemyBullet::BeginPlay()
{
	Super::BeginPlay();

	//플레이어와 자신의 위치를 이용해 방향을 계산
	Dir = (GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - this->GetActorLocation()).GetSafeNormal();
}

// Called every frame
void AEnemyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector p = GetActorLocation() + Dir * Speed * DeltaTime;
	SetActorLocation(p);
}

void AEnemyBullet::OnEnemyBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADestiny2Character* player = Cast<ADestiny2Character>(OtherActor);

	if (player)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Enemy Bullet Attack -> Player"));

		GEngine->AddOnScreenDebugMessage(10, 3.0f, FColor::Blue, TEXT("Enemy Bullet Attack"));

		Destroy();
	}

	else
	{
		Destroy();
	}
}

