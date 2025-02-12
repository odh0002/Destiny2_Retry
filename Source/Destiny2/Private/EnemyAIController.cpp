// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "EnemyBase.h"
#include "Kismet/GameplayStatics.h"

AEnemyAIController::AEnemyAIController()
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	SetPerceptionComponent(*AIPerception);

	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightComfig"));
	if (sightConfig)
	{
		sightConfig->SightRadius = 1000.0f; //AI�� �� �� �ִ� �Ÿ�
		sightConfig->LoseSightRadius = 1200.0f; // �þ߿��� ������ �� �Ÿ�
		sightConfig->PeripheralVisionAngleDegrees = 75.0f; // �þ߰�
		sightConfig->SetMaxAge(5.0f); //���� ���� ���� �ð�
		sightConfig->DetectionByAffiliation.bDetectEnemies = true;
		sightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		sightConfig->DetectionByAffiliation.bDetectFriendlies = false;

		AIPerception->ConfigureSense(*sightConfig);
		AIPerception->SetDominantSense(sightConfig->GetSenseImplementation());
	}

	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetDetected);
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	EnemyCharacter = Cast<AEnemyBase>(GetPawn());
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (LookatPlayer)
	{
		ChasePlayer(GetWorld()->GetFirstPlayerController()->GetPawn());

		//sightConfig->PeripheralVisionAngleDegrees = 130.0f; �þ߰� ������ �̷�� ���� ����
	}
	else
	{
		StopMovement();
	}

	//AEnemyBase* EnemyCharacter = Cast<AEnemyBase>(GetPawn());
	//if (!EnemyCharacter) return;

	//APawn* playerPawn = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	//if (!playerPawn) return;

	//float Distance = FVector::Dist(EnemyCharacter->GetActorLocation(), playerPawn->GetActorLocation());

	//if (Distance <= EnemyCharacter->AttackRange)
	//{
	//	StopMovement();
	//}
	//else
	//{
	//	//MoveToActor(playerPawn, 100.0f);
	//}
}

void AEnemyAIController::OnTargetDetected(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		UE_LOG(LogTemp, Warning, TEXT("Succcess"));
		//ChasePlayer(GetWorld()->GetFirstPlayerController()->GetPawn());
		LookatPlayer = true;

		//MoveToActor(GetWorld()->GetFirstPlayerController()->GetPawn(), 100.0f); //�Ÿ� 100���� �߰�
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Fail"));
		LookatPlayer = false;

		//StopMovement();
	}
}

void AEnemyAIController::ChasePlayer(APawn* Player)
{
	MoveToActor(Player, EnemyCharacter->AttackRange); //�ڽ��� ���� ���� ��ŭ ���ư�
}
