// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FallingSencor.generated.h"

UCLASS()
class DESTINY2_API AFallingSencor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFallingSencor();

protected:

public:	
	

	UPROPERTY(EditAnywhere)
	class USceneCaptureComponent* SceneRoot;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* PlayerSencor;

	UFUNCTION()
	void OnFallingOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
