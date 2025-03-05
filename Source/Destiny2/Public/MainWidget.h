// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class DESTINY2_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	



//protected:
//	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UTextBlock* TotalAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UTextBlock* CurrentAmmo;

public:
	void PrintTotalAmmo(int TotalAmmo) const;
	void PrintCurrentAmmo(int CurrentAmmo, int TotalAmmo) const;
};
