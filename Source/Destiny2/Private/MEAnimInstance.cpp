// Fill out your copyright notice in the Description page of Project Settings.


#include "MEAnimInstance.h"
#include "MeleeEnemy.h"

void UMEAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{

	Super::NativeUpdateAnimation(DeltaSeconds);

	//이 클래스를 갖고 있는 pawn의 정보를 가져옴
	Enemy = Cast<AMeleeEnemy>(TryGetPawnOwner());
	if (!Enemy) return; //없을 경우 아래는 실행 안함

	//캐릭터의 속도를 저장해둠
	FVector velocity = Enemy->GetVelocity();
	//그리고 해당 캐릭터의 앞방향 벡터를 받아옴
	FVector forwardVector = Enemy->GetActorForwardVector();

	// 앞/뒤 이동속도 (외적 Dot을 이용)
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
