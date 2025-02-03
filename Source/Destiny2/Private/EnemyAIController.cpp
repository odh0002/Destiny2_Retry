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
		sightConfig->SightRadius = 1000.0f; //AI가 볼 수 있는 거리
		sightConfig->LoseSightRadius = 1200.0f; // 시야에서 놓쳤을 때 거리
		sightConfig->PeripheralVisionAngleDegrees = 75.0f; // 시야각
		sightConfig->SetMaxAge(5.0f); //감지 정보 유지 시간
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

		//sightConfig->PeripheralVisionAngleDegrees = 130.0f; 시야각 조절은 이루어 지지 않음
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

		//MoveToActor(GetWorld()->GetFirstPlayerController()->GetPawn(), 100.0f); //거리 100까지 추격
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
	MoveToActor(Player, EnemyCharacter->AttackRange); //자신의 공격 범위 만큼 좇아감
}
