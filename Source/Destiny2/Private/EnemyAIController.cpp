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

	//�ʿ� ó������ ��ġ�Ǿ������� �۵��ؼ� EnemyCharacter�� ������
	EnemyCharacter = Cast<AMeleeEnemy>(GetPawn());

	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//���� ������ Begin�� ���� ������ ��츦 ����Ͽ� ƽ���� �����ϰ� ����
	if (!EnemyCharacter)
	{
		EnemyCharacter = Cast<AMeleeEnemy>(GetPawn());
	}

	//�׸��� �������� ��쿡�� �÷��̾� ���� �� ���� ��ȣ�ۿ��� �Ͼ
	else
	{
		//ü���� 0�� �ƴ� ���
		if (EnemyCharacter->Health > 0)
		{
			if (EnemyCharacter->Anim->bIsAttack == false)
			{
				//���Ǿ��� �÷��̾ ����
				ChasePlayer(Player);
			}

			//SetFocus(Player);
		}
		else {
			ClearFocus(EAIFocusPriority::Gameplay);
			StopMovement();
		}

		//float dis = FVector::Distance(EnemyCharacter->GetActorLocation(), Player->GetActorLocation());

		//���� �÷��̾���� �Ÿ��� AttackRange���� ���� ��� ������ ����
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
