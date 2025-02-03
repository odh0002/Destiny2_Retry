// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyAIController.h"

// Sets default values
AMeleeEnemy::AMeleeEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = 150.0f;
	MaxHealth = Health;
	MoveSpeed = 500.0f;
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	
}

// Called when the game starts or when spawned
void AMeleeEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMeleeEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

