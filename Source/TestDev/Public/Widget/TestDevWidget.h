// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestDevWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTDEV_API UTestDevWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* PlayerNickname;
	
private:
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

};
