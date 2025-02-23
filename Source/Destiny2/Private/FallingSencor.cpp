// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingSencor.h"
#include "Components/BoxComponent.h"
#include "Components/SceneCaptureComponent.h"
#include "../Destiny2Character.h"

// Sets default values
AFallingSencor::AFallingSencor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneCaptureComponent>(TEXT("CollisionRoot"));

	PlayerSencor = CreateDefaultSubobject<UBoxComponent>(TEXT("PlayerSencer"));
	PlayerSencor->SetupAttachment(SceneRoot);
	PlayerSencor->SetCollisionProfileName(FName("PlayerSencer"));
	PlayerSencor->OnComponentBeginOverlap.AddDynamic(this, &AFallingSencor::OnFallingOverlap);
}

void AFallingSencor::OnFallingOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADestiny2Character* player = Cast<ADestiny2Character>(OtherActor);

	if (player)
	{
		player->SetActorLocation(FVector(0.0f,0.0f,430.0f));
	}
}

