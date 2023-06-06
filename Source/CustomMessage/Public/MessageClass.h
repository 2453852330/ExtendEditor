// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MessageClass.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMMESSAGE_API UMessageClass : public UObject
{
	GENERATED_BODY()

public:
	/** 用于 UViewportStatsSubsystem 的回调函数 */
	UFUNCTION()
	bool MessageCallback(FText& OutText, FLinearColor& OutColor);

	/** 设置显示内容 */
	void SetMessage(FText InText, FLinearColor InColor);

	/** 打开和关闭消息显示 */
	void ToggleDisplay();

	/** 负责将 MessageCallback 绑定到 ViewportStatsSubsystem */
	void BindToViewportStatsSubsystem();

	/** 查询绑定状态 */
	bool IsBind();

private:
	
	FText Text = FText();
	FLinearColor Color = FLinearColor();
	bool bShouldDisplay = false;
	bool bIsBind = false;
};
