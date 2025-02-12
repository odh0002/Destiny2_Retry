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
	NoWave UMETA(DisplayName = "No_Wave")
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
	virtual void Die();

	//몬스터 스포너에게 몬스터 사망 카운트를 전달하기 위해 클래스 지정 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AEnemySpawner* EnemySpawner;

	//일단 임시로 NoWave라 정함
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	EEnemyWaveState mWaveState = EEnemyWaveState::NoWave;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int32 SetWave = 4;

	////WaveA 지정함수
	//void SetWaveA(AEnemySpawner* Spawner);
	//
	////WaveB 지정함수
	//void SetWaveB(AEnemySpawner* Spawner);
	//
	////WaveC 지정함수
	//void SetWaveC(AEnemySpawner* Spawner);

	void SetWaveA();

	void SetWaveB();

	void SetWaveC();
};
