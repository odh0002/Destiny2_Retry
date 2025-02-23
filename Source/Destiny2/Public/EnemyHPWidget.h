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
	//�̸��� NameText�� TextBlock�� ������Ҵ�.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* NameText;

	//�̸��� HPBar�� UProgressBar�� �����Ų��.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* HPBar;
};
