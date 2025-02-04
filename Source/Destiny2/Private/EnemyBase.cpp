// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyAIController.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	//Base Speed And Health Setting
	Health = 100.0f;
	MaxHealth = Health;
	MoveSpeed = 300.0f;
	//AttackRange = 150.0f;
	//ChaseRange = 100.0f;
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyBase::GetDamage(float DamageAmount)
{
	Health -= DamageAmount;
	// Dead Event
	if (Health <= 0)
	{
		Die();
	}
}

void AEnemyBase::Die()
{
	//AODHTestGameMode* GameMode = Cast<AODHTestGameMode>(GetWorld()->GetAuthGameMode());
	/*if (GameMode)
	{
		GameMode->PlusEnemyDeadCount();
	}
	*/
	SetLifeSpan(3.0f);
}

