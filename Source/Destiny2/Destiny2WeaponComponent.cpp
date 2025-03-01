// Copyright Epic Games, Inc. All Rights Reserved.


#include "Destiny2WeaponComponent.h"
#include "Destiny2Character.h"
#include "Destiny2Projectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Animation/AnimInstance.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"



// Sets default values for this component's properties
UDestiny2WeaponComponent::UDestiny2WeaponComponent()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);

	// 기본 탄약 설정
	MaxAmmo = 20;
	CurrentAmmo = MaxAmmo;
	TotalAmmo = 999;
}



void UDestiny2WeaponComponent::Fire()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Fire() 함수 실행됨!"));

	// 총알이 0이면 발사 불가능
	if (CurrentAmmo <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Ammo! Press 'R' to Reload."));
		return;
	}

	// 총알 발사 성공하면 총알 개수 감소
	CurrentAmmo--;

	UE_LOG(LogTemp, Warning, TEXT("Fired! Remaining Ammo: %d"), CurrentAmmo);


	// Try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
	
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
			// Spawn the projectile at the muzzle
			World->SpawnActor<ADestiny2Projectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}
	// 총알이 0이면 경고 메시지 출력
	if (CurrentAmmo == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Out of Ammo! Press 'R' to Reload."));
	}

	// Try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}
	
	// Try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}




bool UDestiny2WeaponComponent::AttachWeapon(ADestiny2Character* TargetCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("AttachWeapon() 호출됨!"));  // 실행 여부 확인

	if (TargetCharacter == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AttachWeapon() 실패: TargetCharacter가 nullptr입니다!"));
		return false;
	}

	Character = TargetCharacter;

	if (Character == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AttachWeapon() 실패: Character가 nullptr입니다!"));
		return false;
	}



	AController* Controller = Character->GetController();
	if (!Controller)
	{
		UE_LOG(LogTemp, Error, TEXT("AttachWeapon() 실패: Character->GetController()가 nullptr입니다!"));
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UDestiny2WeaponComponent::TryAttachWeaponAgain, 0.1f, false);

		return false;
	}

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("AttachWeapon() 실패: PlayerController가 존재하지 않습니다. AI 캐릭터일 수도 있음."));
		return false;
	}






	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("AttachWeapon: 기존 바인딩 제거 후 새 바인딩 추가"));

		// 기존 FireAction 바인딩을 모두 삭제
		EnhancedInputComponent->ClearActionBindings();

		UE_LOG(LogTemp, Warning, TEXT("AttachWeapon: FireAction 및 ReloadAction 바인딩"));

		// 발사 기능 (Fire)
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &UDestiny2WeaponComponent::Fire);

		// 재장전 기능 (Reload)
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &UDestiny2WeaponComponent::Reload);
	

	}
	// Check that the character is valid, and has no weapon component yet
	if (Character == nullptr || Character->GetInstanceComponents().FindItemByClass<UDestiny2WeaponComponent>())
	{
		UE_LOG(LogTemp, Error, TEXT("AttachWeapon() 실패: 캐릭터가 없거나 이미 무기가 있음!"));
		return false;
	}


	UE_LOG(LogTemp, Warning, TEXT("무기 부착 전 코드 실행됨"));


	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));

	UE_LOG(LogTemp, Warning, TEXT("무기 부착 완료"));

	// Set up action bindings

		//if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		//{
		//	//UE_LOG(LogTemp, Warning, TEXT("AttachWeapon: MappingContext 추가됨"));
		//	// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
		//	Subsystem->AddMappingContext(FireMappingContext, 1);
		//}

		//if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		//{
		//	// Fire
		//	EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &UDestiny2WeaponComponent::Fire);
		//}
	

	return true;
}

void UDestiny2WeaponComponent::TryAttachWeaponAgain()
{
	if (Character && Character->GetController())
	{
		UE_LOG(LogTemp, Warning, TEXT("TryAttachWeaponAgain(): 컨트롤러가 활성화됨. 무기 부착 시도!"));
		AttachWeapon(Character);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TryAttachWeaponAgain(): 여전히 Character 또는 PlayerController가 nullptr입니다. 다시 시도."));
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UDestiny2WeaponComponent::TryAttachWeaponAgain, 0.1f, false);
	}
}

void UDestiny2WeaponComponent::Reload()
{
	if (CurrentAmmo < MaxAmmo)  // 탄창이 다 차지 않은 경우만 재장전 가능
	{
		UE_LOG(LogTemp, Warning, TEXT("Reloading..."));
		CurrentAmmo = MaxAmmo;
		UE_LOG(LogTemp, Warning, TEXT("Reload Complete! Ammo: %d"), CurrentAmmo);
		TotalAmmo = TotalAmmo - MaxAmmo;
		// Try and play a firing animation if specified
		if (ReloadAnimation != nullptr)
		{
			// Get the animation object for the arms mesh
			UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
			if (AnimInstance != nullptr)
			{
				AnimInstance->Montage_Play(ReloadAnimation, 1.f);
				UE_LOG(LogTemp, Warning, TEXT("Reload Animmmmmmm"));
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Ammo is already full!"));
		UE_LOG(LogTemp, Warning, TEXT("Reload Faileddddddddddd"));
	}
}

void UDestiny2WeaponComponent::FinishReload()
{
	CurrentAmmo = MaxAmmo;
	//bIsReloading = false;
	UE_LOG(LogTemp, Warning, TEXT("Reload Complete! Ammo: %d"), CurrentAmmo);
}




void UDestiny2WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// ensure we have a character owner
	if (Character != nullptr)
	{
		// remove the input mapping context from the Player Controller
		if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->RemoveMappingContext(FireMappingContext);
			}
		}
	}

	// maintain the EndPlay call chain
	Super::EndPlay(EndPlayReason);
}


