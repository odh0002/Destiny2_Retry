// Fill out your copyright notice in the Description page of Project Settings.


#include "REAnimInstance.h"
#include "RangedEnemy.h"

void UREAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//�� Ŭ������ ���� �ִ� pawn�� ������ ������
	Enemy = Cast<ARangedEnemy>(TryGetPawnOwner());
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

void UREAnimInstance::AnimNotify_Attack()
{
	//�ش� �ִϸ��̼��� ����� �� ���ʹ��� ����, �Ѿ� ������ �̷������.
	Enemy->Attack();
}

void UREAnimInstance::AnimNotify_Attack2()
{
	//�ش� �ִϸ��̼��� ����� �� ���ʹ��� ����, �Ѿ� ������ �̷������.
	//Enemy->Attack();
}

void UREAnimInstance::AnimNotify_Attack3()
{
	//�ش� �ִϸ��̼��� ����� �� ���ʹ��� ����, �Ѿ� ������ �̷������.
	Enemy->Attack();
}
