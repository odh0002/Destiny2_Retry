// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ARangedEnemy::ARangedEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = 150.0f;
	MaxHealth = Health;
	MoveSpeed = 1000.0f;
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
}

// Called when the game starts or when spawned
void ARangedEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARangedEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARangedEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARangedEnemy::Attack()
{
	if (atkTime <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ranged Enemy Attack"));
		atkTime = 2.0f;
	}
	else { return; }
}

