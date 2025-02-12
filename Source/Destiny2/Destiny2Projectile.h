// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Destiny2Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class ADestiny2Projectile : public AActor
{
	GENERATED_BODY()

public:
	ADestiny2Projectile();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;


	// 충돌 감지
	UPROPERTY(VisibleDefaultsOnly, Category= "Projectile")
	USphereComponent* CollisionComp;


	// 광탄 효과
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	class UNiagaraComponent* ProjectileEffect;


	// 총알 이동
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;


	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	///** Returns CollisionComp subobject **/
	//USphereComponent* GetCollisionComp() const { return CollisionComp; }
	///** Returns ProjectileMovement subobject **/
	//UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};

