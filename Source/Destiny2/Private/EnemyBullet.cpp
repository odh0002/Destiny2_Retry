// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBullet.h"

// Sets default values
AEnemyBullet::AEnemyBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyBullet::BeginPlay()
{
	Super::BeginPlay();

	//�÷��̾�� �ڽ��� ��ġ�� �̿��� ������ ���
	Dir = (GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - this->GetActorLocation()).GetSafeNormal();
}

// Called every frame
void AEnemyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector p = GetActorLocation() + Dir * Speed * DeltaTime;
	SetActorLocation(p);
}

