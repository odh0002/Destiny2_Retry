// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedEnemyAI.h"
#include "RangedEnemy.h"
#include "REAnimInstance.h"

void ARangedEnemyAI::BeginPlay()
{
	Super::BeginPlay();

	//�ʿ� ó������ ��ġ�Ǿ������� �۵��ؼ� EnemyCharacter�� ������
	EnemyCharacter = Cast<ARangedEnemy>(GetPawn());

	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void ARangedEnemyAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//���� ������ Begin�� ���� ������ ��츦 ����Ͽ� ƽ���� �����ϰ� ����
	if (!EnemyCharacter)
	{
		EnemyCharacter = Cast<ARangedEnemy>(GetPawn());
	}

	if (!Anim)
	{
		Anim = Cast<UREAnimInstance>(EnemyCharacter->GetMesh()->GetAnimInstance());
	}

	//�׸��� �������� ��쿡�� �÷��̾� ���� �� ���� ��ȣ�ۿ��� �Ͼ
	else 
	{
		//ü���� 0�� �ƴ� ���
		if (EnemyCharacter->Health > 0)
		{
			SetFocus(Player);

			//���� �̵��� �ƴ� ��� �÷��̾ ����
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

			//RangedATKRange ���� ���� ��� 
			if (FVector::Distance(EnemyCharacter->GetActorLocation(), Player->GetActorLocation()) <= EnemyCharacter->RangedATKRange)
			{
				//���� ���� �̾� ������ ���� ���� �� �ϳ��� �����ϰ� ��
				int32 RandomAction = FMath::RandRange(1, 3);

				switch (RandomAction)
				{
				case 1: //������ ���� ����
					EnemyCharacter->Stand();
					AIStopCalling();
					break;
				case 2: // ���ʹ� ���� �������� �̵��ϸ� ����
					EnemyCharacter->RightMove();
					AIRightMoveCalling();
					break;
				case 3: //���ʹ� ���� ������ �̵��ϸ� ����
					EnemyCharacter->LeftMove();
					AILeftMoveCalling();
					break;
				default:
					break;
				}
			}
			//���� �÷��̾���� �Ÿ��� AttackRange���� ���� ��� ������ ����(�÷��̾ ���� ���� �̵��ϸ鼭 ���ݰ����ҵ�)
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
	MoveToActor(inGamePlayer, EnemyCharacter->ChaseRange); //�ڽ��� ���� ���� ��ŭ ���ư�
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
	//�̵��� ���߰� ��õ��� �������� �ʰ� ����
	//StopMovement();
	moving = true;

	Anim->bRightMove = true;

	//���� �ð� �� �ڵ����� ���� �����ؼ� �÷��̾ �����ϰ� ����
	GetWorld()->GetTimerManager().SetTimer(MovingCalling, this, &ARangedEnemyAI::ChangeMovingBool, 2.5f, false);
}

void ARangedEnemyAI::AILeftMoveCalling()
{
	//�̵��� ���߰� ��õ��� �������� �ʰ� ����
	StopMovement();
	moving = true;

	Anim->bLeftMove = true;

	//���� �ð� �� �ڵ����� ���� �����ؼ� �÷��̾ �����ϰ� ����
	GetWorld()->GetTimerManager().SetTimer(MovingCalling, this, &ARangedEnemyAI::ChangeMovingBool, 2.5f, false);
}

void ARangedEnemyAI::AIStopCalling()
{
	//�̵��� ���߰� ��õ��� �������� �ʰ� ����
	//StopMovement();
	moving = true;

	//���� �ð� �� �ڵ����� ���� �����ؼ� �÷��̾ �����ϰ� ����
	GetWorld()->GetTimerManager().SetTimer(MovingCalling, this, &ARangedEnemyAI::ChangeMovingBool, 2.5f, false);
}
