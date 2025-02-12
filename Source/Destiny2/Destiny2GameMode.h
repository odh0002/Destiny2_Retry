// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Destiny2GameMode.generated.h"

UCLASS(minimalapi)
class ADestiny2GameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	ADestiny2GameMode();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> mainWidget;


private:
	class UMainWidget* mainUI;
};



