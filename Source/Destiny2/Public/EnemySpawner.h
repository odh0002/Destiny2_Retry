// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MeleeEnemy.h"
#include "RangedEnemy.h"
#include "GameClearActor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class DESTINY2_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//근접 에너미 소환 테스트한거
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AMeleeEnemy> MeleeEnemy;

	//원거리 에너미 소환 테스트한거
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ARangedEnemy> RangedEnemy;

	float CurTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnTime = 1.4f;

	//몬스터 웨이브 A들의 정보를 저장하는 곳
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class AEnemyBase>> WaveA;

	//몬스터 웨이브A가 소환됐는지 확인하는 변수
	bool bWaveA = false;

	//몬스터 웨이브 B들의 정보를 저장하는 곳
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class AEnemyBase>> WaveB;

	//몬스터 웨이브B가 소환됐는지 확인하는 변수
	bool bWaveB = false;

	//몬스터 웨이브 C들의 정보를 저장하는 곳
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class AEnemyBase>> WaveC;

	//몬스터 웨이브C가 소환됐는지 확인하는 변수
	bool bWaveC = false;

	//아래는 각각 웨이브 소환 조건이 만족했는지 확인하는 변수
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool Fight = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool WaveAClera = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool WaveBClera = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool WaveCClera = false;

	void SpawnEnemyWave(TArray<TSubclassOf<AEnemyBase>> Wave, int32 WaveNum);

	//각각의 웨이브 에너미들의 총 마리 수를 저장하기 위한 변수들
	int32 WaveAEnemys = 0;
	int32 WaveBEnemys = 0;
	int32 WaveCEnemys = 0;

	//각 에너미들이 죽을 경우 숫자를 받아서 각 상황에 맞게 카운트를 줄여줌
	void WaveEnemyCountDown(int32 WaveNum);

	TArray<AActor*> spawnPoints;

	void SetSpawnPoints();

	int32 RandomSpawnPoint();

	FTimerHandle MethodCalling;

	UFUNCTION(BlueprintCallable, Category = "Fight")
	void OnPlayer();

	UPROPERTY(EditInstanceOnly)
	class AGameClearActor* ClearActor;
};
