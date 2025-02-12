// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class DESTINY2_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
	public:
	AEnemyAIController();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "AI")
	class UAIPerceptionComponent* AIPerception;

	UPROPERTY(EditAnywhere, Category = "AI")
	class UAISenseConfig_Sight* sightConfig;

	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus Stimulus); //시야 내에 플레이어가 들어왔는지 확인하는 함수

	void ChasePlayer(APawn* Player); // 플레이어를 좇는 함수

	bool LookatPlayer = false; //플레이어를 발견했는지 확인하는 불

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AEnemyBase* EnemyCharacter; //자신의 공격 범위를 전 지역에서 쓰기 위해 클래스 지정
};
