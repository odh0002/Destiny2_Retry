// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Kismet/GameplayStatics.h"
#include "MeleeEnemy.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	EnemyCharacter = Cast<AMeleeEnemy>(GetPawn());

	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//ü���� 0�� �ƴ� ���
	if(EnemyCharacter->Health >= 0 )
	{ 
		//���Ǿ��� �÷��̾ ����
		ChasePlayer(Player);
		SetFocus(Player);
	}
	else { return; }


	//float dis = FVector::Distance(EnemyCharacter->GetActorLocation(), Player->GetActorLocation());
	
	//���� �÷��̾���� �Ÿ��� AttackRange���� ���� ��� ������ ����
	if (FVector::Distance(EnemyCharacter->GetActorLocation(), Player->GetActorLocation()) <= EnemyCharacter->AttackRange)
	{
		EnemyCharacter->Attack();
	}
	else { return; }
		
	//if (LookatPlayer)
	//{
	//	ChasePlayer(GetWorld()->GetFirstPlayerController()->GetPawn());
	//
	//	//sightConfig->PeripheralVisionAngleDegrees = 130.0f; �þ߰� ������ �̷�� ���� ����
	//}
	//else
	//{
	//	StopMovement();
	//}
	//
	//AEnemyBase* EnemyCharacter = Cast<AEnemyBase>(GetPawn());
	//if (!EnemyCharacter) return;
	//
	//APawn* playerPawn = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	//if (!playerPawn) return;
	//
	//float Distance = FVector::Dist(EnemyCharacter->GetActorLocation(), playerPawn->GetActorLocation());
	//
	//if (Distance <= EnemyCharacter->AttackRange)
	//{
	//	StopMovement();
	//}
	//else
	//{
	//	//MoveToActor(playerPawn, 100.0f);
	//}
}

void AEnemyAIController::ChasePlayer(APawn* inGamePlayer)
{
	MoveToActor(inGamePlayer, EnemyCharacter->ChaseRange); //�ڽ��� ���� ���� ��ŭ ���ư�
}
