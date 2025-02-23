// Fill out your copyright notice in the Description page of Project Settings.


#include "MEAnimInstance.h"
#include "MeleeEnemy.h"

void UMEAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{

	Super::NativeUpdateAnimation(DeltaSeconds);

	//�� Ŭ������ ���� �ִ� pawn�� ������ ������
	Enemy = Cast<AMeleeEnemy>(TryGetPawnOwner());
	if (!Enemy) return; //���� ��� �Ʒ��� ���� ����

	//ĳ������ �ӵ��� �����ص�
	FVector velocity = Enemy->GetVelocity();
	//�׸��� �ش� ĳ������ �չ��� ���͸� �޾ƿ�
	FVector forwardVector = Enemy->GetActorForwardVector();

	// ��/�� �̵��ӵ� (���� Dot�� �̿�)
	Speed = FVector::DotProduct(velocity, forwardVector);

	FVector RightVector = Enemy->GetActorRightVector();

	Direction = FVector::DotProduct(velocity, RightVector);
}

void UMEAnimInstance::AnimNotify_AttackEnd()
{
	if (Enemy)
	{
		bIsAttack = false;
	}
}

void UMEAnimInstance::AnimNotify_OnCollision()
{
	Enemy->OnWeaponCollision();
}

void UMEAnimInstance::AnimNotify_OffCollision()
{
	Enemy->OffWeaponCollision();
}
