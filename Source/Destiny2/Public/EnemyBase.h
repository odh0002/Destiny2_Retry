// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

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
	float AttackRange = 0.0f;

	virtual void Attack();

	virtual void GetDamage(float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "DEAD")
	virtual void Die();

};
