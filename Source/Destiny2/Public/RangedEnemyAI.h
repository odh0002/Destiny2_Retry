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

	void ChasePlayer(APawn* inGamePlayer); // 플레이어를 좇는 함수

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class ARangedEnemy* EnemyCharacter; //자신의 공격 범위를 전 지역에서 쓰기 위해 클래스 지정

	class APawn* Player;

	FTimerHandle MovingCalling;
	bool moving = false;

	void ChangeMovingBool();

	void AIRightMoveCalling();
	void AILeftMoveCalling();
	void AIStopCalling();
};
