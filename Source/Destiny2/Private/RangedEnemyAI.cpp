// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedEnemyAI.h"
#include "RangedEnemy.h"

void ARangedEnemyAI::BeginPlay()
{
	Super::BeginPlay();

	EnemyCharacter = Cast<ARangedEnemy>(GetPawn());

	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void ARangedEnemyAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//체력이 0이 아닐 경우
	if (EnemyCharacter->Health >= 0)
	{
		//조건없이 플레이어를 좇음
		ChasePlayer(Player);
		SetFocus(Player);
	}
	else { return; }

	//만약 플레이어와의 거리가 AttackRange보다 적을 경우 공격을 실행
	if (FVector::Distance(EnemyCharacter->GetActorLocation(), Player->GetActorLocation()) <= EnemyCharacter->AttackRange)
	{
		EnemyCharacter->Attack();
	}
	else { return; }
}

void ARangedEnemyAI::ChasePlayer(APawn* inGamePlayer)
{
	MoveToActor(inGamePlayer, EnemyCharacter->ChaseRange); //자신의 공격 범위 만큼 좇아감
}
