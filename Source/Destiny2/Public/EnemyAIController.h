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
	void OnTargetDetected(AActor* Actor, FAIStimulus Stimulus); //�þ� ���� �÷��̾ ���Դ��� Ȯ���ϴ� �Լ�

	void ChasePlayer(APawn* Player); // �÷��̾ ���� �Լ�

	bool LookatPlayer = false; //�÷��̾ �߰��ߴ��� Ȯ���ϴ� ��

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AEnemyBase* EnemyCharacter; //�ڽ��� ���� ������ �� �������� ���� ���� Ŭ���� ����
};
