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

	float CurTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ATKDelayTime = 3.7f;

	class APawn* Player;

	FTimerHandle MovingCalling;
	bool moving = false;

	void ChangeMovingBool();

	void AIRightMoveCalling();
	void AILeftMoveCalling();
	void AIStopCalling();

public:
	void Setlocation(FVector Location);


	UPROPERTY()
	class UREAnimInstance* Anim;
};
