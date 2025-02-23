// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "REAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DESTINY2_API UREAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	class ARangedEnemy* Enemy;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = REAnimInst)
	float Speed = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = REAnimInst)
	float Direction = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = REAnimInst)
	bool bRightMove = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = REAnimInst)
	bool bLeftMove = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = REAnimInst)
	bool bIsDead = false;

	//���ݿ� ���� ��Ÿ�ָ� �ޱ� ���� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = REAnimInst)
	class UAnimMontage* REMontage;

	//�ִϸ��̼ǿ��� �ش� �κ��� ����Ǹ� ����Ǵ� �Լ�
	UFUNCTION()
	void AnimNotify_Attack();

	UFUNCTION()
	void AnimNotify_Attack2();

	UFUNCTION()
	void AnimNotify_Attack3();
};
