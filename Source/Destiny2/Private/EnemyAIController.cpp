// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Kismet/GameplayStatics.h"
#include "MeleeEnemy.h"
#include "MEAnimInstance.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	//맵에 처음부터 배치되어있을때 작동해서 EnemyCharacter에 저장함
	EnemyCharacter = Cast<AMeleeEnemy>(GetPawn());

	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//만약 위에서 Begin때 되지 못했을 경우를 대비하여 틱에서 실행하게 만듦
	if (!EnemyCharacter)
	{
		EnemyCharacter = Cast<AMeleeEnemy>(GetPawn());
	}

	//그리고 성공했을 경우에만 플레이어 추적 및 공격 상호작용이 일어남
	else
	{
		//체력이 0이 아닐 경우
		if (EnemyCharacter->Health > 0)
		{
			if (EnemyCharacter->Anim->bIsAttack == false)
			{
				//조건없이 플레이어를 추적
				ChasePlayer(Player);
			}

			//SetFocus(Player);
		}
		else {
			ClearFocus(EAIFocusPriority::Gameplay);
			StopMovement();
		}

		//float dis = FVector::Distance(EnemyCharacter->GetActorLocation(), Player->GetActorLocation());

		//만약 플레이어와의 거리가 AttackRange보다 적을 경우 공격을 실행
		if (FVector::Distance(EnemyCharacter->GetActorLocation(), Player->GetActorLocation()) <= EnemyCharacter->AttackRange)
		{
			EnemyCharacter->Attack();
		}
		else { return; }
	}
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
