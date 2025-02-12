// Copyright Epic Games, Inc. All Rights Reserved.

#include "Destiny2Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"  
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

ADestiny2Projectile::ADestiny2Projectile()
{


    // 충돌 감지를 위한 구체 콜리전 컴포넌트
    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    CollisionComp->InitSphereRadius(2.5f);
    CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
    CollisionComp->OnComponentHit.AddDynamic(this, &ADestiny2Projectile::OnHit);
    // [추가] 물리 상호작용 활성화
    CollisionComp->SetSimulatePhysics(false);   // 투사체 자체는 물리적용 X (움직임은 ProjectileMovement가 담당)
    CollisionComp->SetNotifyRigidBodyCollision(true);  // 물리 충돌 이벤트 활성화
    CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);  // 물리 & 충돌 감지 활성화
    CollisionComp->SetCollisionObjectType(ECC_PhysicsBody);  // 물리 객체로 설정
    CollisionComp->SetCollisionResponseToAllChannels(ECR_Block);  // 모든 채널에서 충돌 감지
    CollisionComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);  // 바닥 & 벽과 충돌 가능
    RootComponent = CollisionComp;

    // 광탄 파티클 효과 추가
    ProjectileEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileEffect"));
    ProjectileEffect->SetupAttachment(RootComponent);

    // 광탄 이펙트 기본값 설정
    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraAsset(TEXT("/Game/LJY/VFX/P_Beam.P_Beam"));
    if (NiagaraAsset.Succeeded())
    {
        ProjectileEffect->SetAsset(NiagaraAsset.Object);
    }

    // 총알 이동 설정
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
    ProjectileMovement->UpdatedComponent = CollisionComp;
    ProjectileMovement->InitialSpeed = 7000.f;  // 광탄 속도 조정
    ProjectileMovement->MaxSpeed = 7000.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = false;
    ProjectileMovement->ProjectileGravityScale = 0.0f;  // 중력 영향 X

    InitialLifeSpan = 3.0f; // 자동 삭제 (3초 후)
}


void ADestiny2Projectile::BeginPlay()
{
    Super::BeginPlay();  // 부모 클래스의 BeginPlay() 실행
}

void ADestiny2Projectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);  // 부모 클래스의 Tick() 실행
}


void ADestiny2Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    UE_LOG(LogTemp, Warning, TEXT("Projectile Hit Something!"));  // 충돌 확인 로그

    if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
    {
        UE_LOG(LogTemp, Warning, TEXT("Projectile Hit a Physics Object!"));  // 물리 객체 충돌 확인 로그

        OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());  // 물리 충격 적용
    }

    // 충돌 즉시 폭발 이펙트 추가 가능
    UNiagaraSystem* ExplosionEffect = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/LJY/VFX/P_GlowBullet.P_GlowBullet"));
    if (ProjectileEffect)
    {
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
    }
    
    Destroy();  // 충돌 시 즉시 사라짐
}