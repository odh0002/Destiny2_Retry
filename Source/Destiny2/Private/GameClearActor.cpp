// Fill out your copyright notice in the Description page of Project Settings.


#include "GameClearActor.h"
#include "Components/BoxComponent.h"

// Sets default values
AGameClearActor::AGameClearActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	SetRootComponent(Collision);
	Collision->SetBoxExtent(FVector(50.0f));
	Collision->SetCollisionProfileName(FName("PlayerSencer"));
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AGameClearActor::OnPlayerOverlap);

	Static = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static"));
	Static->SetupAttachment(Collision);
}

// Called when the game starts or when spawned
void AGameClearActor::BeginPlay()
{
	Super::BeginPlay();
	
	Static->SetVisibility(false);
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called every frame
void AGameClearActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GameClear)
	{
		return;
	}

	else
	{
		GEngine->AddOnScreenDebugMessage(20, 3.0f, FColor::Green, TEXT("Stage Clear"));
	}
}

void AGameClearActor::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!GameClear)
	{
		GameClear = true;
	}
}

void AGameClearActor::WaveEnd()
{
	Static->SetVisibility(true);
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

