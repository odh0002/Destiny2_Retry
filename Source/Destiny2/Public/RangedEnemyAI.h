// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RangedEnemyAI.generated.h"

/**
 * 
 */
UCLASS()
class DESTINY2_API ARangedEnemyAI : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void ChasePlayer(APawn* inGamePlayer); // �÷��̾ ���� �Լ�

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class ARangedEnemy* EnemyCharacter; //�ڽ��� ���� ������ �� �������� ���� ���� Ŭ���� ����

	class APawn* Player;

	FTimerHandle MovingCalling;
	bool moving = false;

	void ChangeMovingBool();

	void AIRightMoveCalling();
	void AILeftMoveCalling();
	void AIStopCalling();
};
