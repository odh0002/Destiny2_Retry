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

	//ü���� 0�� �ƴ� ���
	if (EnemyCharacter->Health >= 0)
	{
		//���Ǿ��� �÷��̾ ����
		ChasePlayer(Player);
		SetFocus(Player);
	}
	else { return; }

	//���� �÷��̾���� �Ÿ��� AttackRange���� ���� ��� ������ ����
	if (FVector::Distance(EnemyCharacter->GetActorLocation(), Player->GetActorLocation()) <= EnemyCharacter->AttackRange)
	{
		EnemyCharacter->Attack();
	}
	else { return; }
}

void ARangedEnemyAI::ChasePlayer(APawn* inGamePlayer)
{
	MoveToActor(inGamePlayer, EnemyCharacter->ChaseRange); //�ڽ��� ���� ���� ��ŭ ���ư�
}
