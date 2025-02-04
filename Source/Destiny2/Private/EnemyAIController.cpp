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

	//체력이 0이 아닐 경우
	if(EnemyCharacter->Health >= 0 )
	{ 
		//조건없이 플레이어를 좇음
		ChasePlayer(Player);
		SetFocus(Player);
	}
	else { return; }


	//float dis = FVector::Distance(EnemyCharacter->GetActorLocation(), Player->GetActorLocation());
	
	//만약 플레이어와의 거리가 AttackRange보다 적을 경우 공격을 실행
	if (FVector::Distance(EnemyCharacter->GetActorLocation(), Player->GetActorLocation()) <= EnemyCharacter->AttackRange)
	{
		EnemyCharacter->Attack();
	}
	else { return; }
		
	//if (LookatPlayer)
	//{
	//	ChasePlayer(GetWorld()->GetFirstPlayerController()->GetPawn());
	//
	//	//sightConfig->PeripheralVisionAngleDegrees = 130.0f; 시야각 조절은 이루어 지지 않음
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
	MoveToActor(inGamePlayer, EnemyCharacter->ChaseRange); //자신의 공격 범위 만큼 좇아감
}
