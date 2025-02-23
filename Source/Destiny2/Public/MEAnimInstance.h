// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MEAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DESTINY2_API UMEAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:

	class AMeleeEnemy* Enemy;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = MEAnimInst)
	float Speed = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = MEAnimInst)
	float Direction = 0.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = MEAnimInst)
	bool bIsDead = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MEAnimInst)
	bool bIsAttack = false;

	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_OnCollision();

	UFUNCTION()
	void AnimNotify_OffCollision();
};
