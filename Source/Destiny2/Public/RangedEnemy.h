// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.h"
#include "EnemyBullet.h"
#include "RangedEnemy.generated.h"

UCLASS()
class DESTINY2_API ARangedEnemy : public AEnemyBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARangedEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<class AEnemyBullet> Bullet;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UArrowComponent* Arrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* WeakCollision;

	int32 ActionNum;
	FVector Dir;

	void Attack(); //총알을 쏘는 함수 나중에 애니메이션을 넣으면 notify를 사용해서 해당 함수를 호출해 총알을 발사하면 될듯

	void LeftMove(); //왼쪽으로 움직이게 만들어주는 함수
	void RightMove(); //오른쪽으로 움직이게 만들어주는 함수
	void Stand(); //가만히 서있게 만들어주는 함수

	void ActionNumReset(); // 위에 이동과 관련된 함수가 끝난 다음에 다시 정상적으로 이동하게 만들기 위한 함수

	float atkTime = 0.0f;

	class ARangedEnemyAI* AIController;

	UFUNCTION()
	void OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnWeakOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
