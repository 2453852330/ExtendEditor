// Fill out your copyright notice in the Description page of Project Settings.


#include "MessageClass.h"

#include "Editor.h"
#include "LevelEditorViewport.h"
#include "Engine/ViewportStatsSubsystem.h"

bool UMessageClass::MessageCallback(FText& OutText, FLinearColor& OutColor)
{
	OutText = Text;
	OutColor = Color;
	return bShouldDisplay;
}

void UMessageClass::SetMessage(FText InText, FLinearColor InColor)
{
	Text = InText;
	Color = InColor;
}

void UMessageClass::ToggleDisplay()
{
	bShouldDisplay = !bShouldDisplay;
}

void UMessageClass::BindToViewportStatsSubsystem()
{
	if(UViewportStatsSubsystem* ViewportSubsystem = 
		GEditor->GetLevelViewportClients()[0]->GetWorld()->GetSubsystem<UViewportStatsSubsystem>())
	{
		FViewportDisplayCallback Callback;
		Callback.BindDynamic(this, &UMessageClass::MessageCallback);
		ViewportSubsystem->AddDisplayDelegate(Callback);
	}

	bIsBind = true;
}

bool UMessageClass::IsBind()
{
	return bIsBind;
}