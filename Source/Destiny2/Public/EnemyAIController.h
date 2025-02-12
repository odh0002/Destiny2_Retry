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

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void ChasePlayer(APawn* inGamePlayer); // �÷��̾ ���� �Լ�

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AMeleeEnemy* EnemyCharacter; //�ڽ��� ���� ������ �� �������� ���� ���� Ŭ���� ����

	class APawn* Player;
};
