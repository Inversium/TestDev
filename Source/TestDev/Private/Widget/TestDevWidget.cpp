// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget\TestDevWidget.h"
#include "Components/TextBlock.h"
#include "TestDevGameState.h"

void UTestDevWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	auto GameState = GetOwningPlayer()->GetWorld()->GetGameState<ATestDevGameState>();
	
	/* Update player nickname from GameState */
	FString NicknameInfo = TEXT("Nickname of the player on plate: ");
	if (GameState) NicknameInfo += GameState->GetPlatePlayerName().ToString();
	if (PlayerNickname) PlayerNickname->SetText(FText::FromString(NicknameInfo));
}
