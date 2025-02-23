// Fill out your copyright notice in the Description page of Project Settings.


#include "REAnimInstance.h"
#include "RangedEnemy.h"

void UREAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//이 클래스를 갖고 있는 pawn의 정보를 가져옴
	Enemy = Cast<ARangedEnemy>(TryGetPawnOwner());
	if (!Enemy) return; //없을 경우 아래는 실행 안함

	//캐릭터의 속도를 저장해둠
	FVector velocity = Enemy->GetVelocity();
	//그리고 해당 캐릭터의 앞방향 벡터를 받아옴
	FVector forwardVector = Enemy->GetActorForwardVector();

	// 앞/뒤 이동속도 (내적 Dot을 이용)
	Speed = FVector::DotProduct(velocity, forwardVector);

	FVector RightVector = Enemy->GetActorRightVector();

	Direction = FVector::DotProduct(velocity, RightVector);
}

void UREAnimInstance::AnimNotify_Attack()
{
	//해당 애니메이션이 재생될 때 에너미의 공격, 총알 스폰이 이루어진다.
	Enemy->Attack();
}

void UREAnimInstance::AnimNotify_Attack2()
{
	//해당 애니메이션이 재생될 때 에너미의 공격, 총알 스폰이 이루어진다.
	//Enemy->Attack();
}

void UREAnimInstance::AnimNotify_Attack3()
{
	//해당 애니메이션이 재생될 때 에너미의 공격, 총알 스폰이 이루어진다.
	Enemy->Attack();
}
