// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHPWidget.generated.h"

/**
 * 
 */
UCLASS()
class DESTINY2_API UEnemyHPWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	//이름이 NameText인 TextBlock과 연결시켠다.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* NameText;

	//이름이 HPBar인 UProgressBar와 연결시킨다.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* HPBar;
};
