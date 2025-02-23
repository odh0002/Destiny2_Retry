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

	void Attack(); //�Ѿ��� ��� �Լ� ���߿� �ִϸ��̼��� ������ notify�� ����ؼ� �ش� �Լ��� ȣ���� �Ѿ��� �߻��ϸ� �ɵ�

	void LeftMove(); //�������� �����̰� ������ִ� �Լ�
	void RightMove(); //���������� �����̰� ������ִ� �Լ�
	void Stand(); //������ ���ְ� ������ִ� �Լ�

	void ActionNumReset(); // ���� �̵��� ���õ� �Լ��� ���� ������ �ٽ� ���������� �̵��ϰ� ����� ���� �Լ�

	float atkTime = 0.0f;

	class ARangedEnemyAI* AIController;

	UFUNCTION()
	void OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnWeakOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
