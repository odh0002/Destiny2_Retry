// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CrossHairWidget.generated.h"

/**
 * 
 */
UCLASS()
class DESTINY2_API UCrossHairWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CrossHairSpread = 10; // 크로스헤어 퍼지는 범위

};
