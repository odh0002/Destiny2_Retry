// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UENUM()
enum class EEnemyWaveState :uint8
{
	WaveA UMETA(DisplayName = "WaveA_Enemy"),
	WaveB UMETA(DisplayName = "WaveB_Enemy"),
	WaveC UMETA(DisplayName = "WaveC_Enemy"),
	NoWave UMETA(DisplayName = "No_Wave"),
};

UCLASS()
class DESTINY2_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Enemy State Base
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Stats")
	float Health = 0.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Stats")
	float MaxHealth = 0.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Stats")
	float MoveSpeed = 0.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "AI")
	float ChaseRange = 0.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = AI)
	float RangedATKRange = 0.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "AI")
	float AttackRange = 0.0f;

	virtual void GetDamage(float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "DEAD")
	void Die();

	//���� �����ʿ��� ���� ��� ī��Ʈ�� �����ϱ� ���� Ŭ���� ���� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AEnemySpawner* EnemySpawner;

	//�ϴ� �ӽ÷� NoWave�� ����
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	EEnemyWaveState mWaveState = EEnemyWaveState::NoWave;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int32 SetWave = 4;

	void SetWaveA();

	void SetWaveB();

	void SetWaveC();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyOwner)
	class AEnemyBase* EnemyOwner;

	//������� ���� ������ �޴°�?
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> EnemyWidget;

	//�� ��Ʈ�� �ε�� ���� ����� ����
	class UEnemyHPWidget* EnemyUI;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyOwner)
	int32 EnemyType = 0;
};
