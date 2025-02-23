// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.h"
#include "MeleeEnemy.generated.h"

UCLASS()
class DESTINY2_API AMeleeEnemy : public AEnemyBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMeleeEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Attack();

	float atkTime = 0.0f;

	class AEnemyAIController* MeleeAI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* HeadCollision;

	class UMEAnimInstance* Anim; //�ִϸ��̼��� �ڵ忡�� �����ϱ����� �ϴ� ����

	//���⿡ �����Ǵ� �ݸ���
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UBoxComponent* WeaponCollision;
	
	//������ �̸��� �����ϴ� ����
	FName SoketName = TEXT("FX_Trail_R_01");

	//���� ��ġ�� �����ϴ� FVector ����
	FVector PreLocation;

	//������ �ݸ����� Ȱ��ȭ�ϴ� ����
	void OnWeaponCollision();

	//������ �ݸ����� ��Ȱ��ȭ�ϴ� ����
	void OffWeaponCollision();

	UFUNCTION()
	void OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnHeadOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};