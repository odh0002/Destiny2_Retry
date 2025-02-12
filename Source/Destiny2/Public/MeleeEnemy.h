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

};
