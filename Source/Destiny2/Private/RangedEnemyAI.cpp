// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedEnemyAI.h"
#include "RangedEnemy.h"
#include "REAnimInstance.h"

void ARangedEnemyAI::BeginPlay()
{
	Super::BeginPlay();

	//맵에 처음부터 배치되어있을때 작동해서 EnemyCharacter에 저장함
	EnemyCharacter = Cast<ARangedEnemy>(GetPawn());

	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void ARangedEnemyAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//만약 위에서 Begin때 되지 못했을 경우를 대비하여 틱에서 실행하게 만듦
	if (!EnemyCharacter)
	{
		EnemyCharacter = Cast<ARangedEnemy>(GetPawn());
	}

	if (!Anim)
	{
		Anim = Cast<UREAnimInstance>(EnemyCharacter->GetMesh()->GetAnimInstance());
	}

	//그리고 성공했을 경우에만 플레이어 추적 및 공격 상호작용이 일어남
	else 
	{
		//체력이 0이 아닐 경우
		if (EnemyCharacter->Health > 0)
		{
			SetFocus(Player);

			//공격 이동이 아닐 경우 플레이어를 좇음
			if (moving == false)
			{
				ChasePlayer(Player);

				CurTime += DeltaSeconds;

				if (CurTime >= ATKDelayTime)
				{
					EnemyCharacter->Attack();
					CurTime = 0.0f;
				}
			}	

			else
			{
				
				CurTime = 0.0f;
				return;
			}

			//RangedATKRange 보다 적을 경우 
			if (FVector::Distance(EnemyCharacter->GetActorLocation(), Player->GetActorLocation()) <= EnemyCharacter->RangedATKRange)
			{
				//랜덤 값을 뽑아 세가지 공격 패턴 중 하나를 실행하게 됨
				int32 RandomAction = FMath::RandRange(1, 3);

				switch (RandomAction)
				{
				case 1: //가만히 서서 공격
					EnemyCharacter->Stand();
					AIStopCalling();
					break;
				case 2: // 에너미 기준 오른쪽을 이동하며 공격
					EnemyCharacter->RightMove();
					AIRightMoveCalling();
					break;
				case 3: //에너미 기준 왼쪽을 이동하며 공격
					EnemyCharacter->LeftMove();
					AILeftMoveCalling();
					break;
				default:
					break;
				}
			}
			//만약 플레이어와의 거리가 AttackRange보다 적을 경우 공격을 실행(플레이어를 향해 직선 이동하면서 공격가능할듯)
			/*else if (FVector::Distance(EnemyCharacter->GetActorLocation(), Player->GetActorLocation()) <= EnemyCharacter->AttackRange)
			{
				EnemyCharacter->Attack();
			}*/
			else { return; }

		}
		else { ClearFocus(EAIFocusPriority::Gameplay);
		StopMovement();
		}

	}
}

void ARangedEnemyAI::ChasePlayer(APawn* inGamePlayer)
{
	MoveToActor(inGamePlayer, EnemyCharacter->ChaseRange); //자신의 공격 범위 만큼 좇아감
}

void ARangedEnemyAI::ChangeMovingBool()
{
	moving = !moving;

	Anim->bRightMove = false;
	Anim->bLeftMove = false;

	EnemyCharacter->ActionNumReset();
}

void ARangedEnemyAI::AIRightMoveCalling()
{
	//이동을 멈추고 잠시동안 움직이지 않게 만듦
	//StopMovement();
	moving = true;

	Anim->bRightMove = true;

	//일정 시간 후 자동으로 불을 변경해서 플레이어를 추적하게 변경
	GetWorld()->GetTimerManager().SetTimer(MovingCalling, this, &ARangedEnemyAI::ChangeMovingBool, 2.5f, false);
}

void ARangedEnemyAI::AILeftMoveCalling()
{
	//이동을 멈추고 잠시동안 움직이지 않게 만듦
	StopMovement();
	moving = true;

	Anim->bLeftMove = true;

	//일정 시간 후 자동으로 불을 변경해서 플레이어를 추적하게 변경
	GetWorld()->GetTimerManager().SetTimer(MovingCalling, this, &ARangedEnemyAI::ChangeMovingBool, 2.5f, false);
}

void ARangedEnemyAI::AIStopCalling()
{
	//이동을 멈추고 잠시동안 움직이지 않게 만듦
	//StopMovement();
	moving = true;

	//일정 시간 후 자동으로 불을 변경해서 플레이어를 추적하게 변경
	GetWorld()->GetTimerManager().SetTimer(MovingCalling, this, &ARangedEnemyAI::ChangeMovingBool, 2.5f, false);
}
