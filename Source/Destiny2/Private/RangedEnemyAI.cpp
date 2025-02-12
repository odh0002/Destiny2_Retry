// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedEnemyAI.h"
#include "RangedEnemy.h"

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

	//�׸��� �������� ��쿡�� �÷��̾� ���� �� ���� ��ȣ�ۿ��� �Ͼ
	else 
	{
		//ü���� 0�� �ƴ� ���
		if (EnemyCharacter->Health >= 0)
		{
			//���� �̵��� �ƴ� ��� �÷��̾ ����
			if (moving == false)
			{
				ChasePlayer(Player);
			}
			SetFocus(Player);

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
		else { return; }

	}
}

void ARangedEnemyAI::ChasePlayer(APawn* inGamePlayer)
{
	MoveToActor(inGamePlayer, EnemyCharacter->ChaseRange); //�ڽ��� ���� ���� ��ŭ ���ư�
}

void ARangedEnemyAI::ChangeMovingBool()
{
	moving = !moving;
	EnemyCharacter->ActionNumReset();
}

void ARangedEnemyAI::AIRightMoveCalling()
{
	//�̵��� ���߰� ��õ��� �������� �ʰ� ����
	StopMovement();
	moving = true;

	//���� �ð� �� �ڵ����� ���� �����ؼ� �÷��̾ �����ϰ� ����
	GetWorld()->GetTimerManager().SetTimer(MovingCalling, this, &ARangedEnemyAI::ChangeMovingBool, 5.0f, false);
}

void ARangedEnemyAI::AILeftMoveCalling()
{
	//�̵��� ���߰� ��õ��� �������� �ʰ� ����
	StopMovement();
	moving = true;

	//���� �ð� �� �ڵ����� ���� �����ؼ� �÷��̾ �����ϰ� ����
	GetWorld()->GetTimerManager().SetTimer(MovingCalling, this, &ARangedEnemyAI::ChangeMovingBool, 5.0f, false);
}

void ARangedEnemyAI::AIStopCalling()
{
	//�̵��� ���߰� ��õ��� �������� �ʰ� ����
	StopMovement();
	moving = true;

	//���� �ð� �� �ڵ����� ���� �����ؼ� �÷��̾ �����ϰ� ����
	GetWorld()->GetTimerManager().SetTimer(MovingCalling, this, &ARangedEnemyAI::ChangeMovingBool, 5.0f, false);
}
