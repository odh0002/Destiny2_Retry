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

	//���� ���ʹ� ��ȯ �׽�Ʈ�Ѱ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AMeleeEnemy> MeleeEnemy;

	//���Ÿ� ���ʹ� ��ȯ �׽�Ʈ�Ѱ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ARangedEnemy> RangedEnemy;

	float CurTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnTime = 1.4f;

	//���� ���̺� A���� ������ �����ϴ� ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class AEnemyBase>> WaveA;

	//���� ���̺�A�� ��ȯ�ƴ��� Ȯ���ϴ� ����
	bool bWaveA = false;

	//���� ���̺� B���� ������ �����ϴ� ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class AEnemyBase>> WaveB;

	//���� ���̺�B�� ��ȯ�ƴ��� Ȯ���ϴ� ����
	bool bWaveB = false;

	//���� ���̺� C���� ������ �����ϴ� ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class AEnemyBase>> WaveC;

	//���� ���̺�C�� ��ȯ�ƴ��� Ȯ���ϴ� ����
	bool bWaveC = false;

	//�Ʒ��� ���� ���̺� ��ȯ ������ �����ߴ��� Ȯ���ϴ� ����
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool Fight = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool WaveAClera = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool WaveBClera = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool WaveCClera = false;

	void SpawnEnemyWave(TArray<TSubclassOf<AEnemyBase>> Wave, int32 WaveNum);

	//������ ���̺� ���ʹ̵��� �� ���� ���� �����ϱ� ���� ������
	int32 WaveAEnemys = 0;
	int32 WaveBEnemys = 0;
	int32 WaveCEnemys = 0;

	//�� ���ʹ̵��� ���� ��� ���ڸ� �޾Ƽ� �� ��Ȳ�� �°� ī��Ʈ�� �ٿ���
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
