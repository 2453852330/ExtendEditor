// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "CustomWidget.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMSLATE_API UCustomWidget : public UWidget
{
	GENERATED_BODY()
	
	/** 释放 MyCustomWidget */
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	/** 更新 MyCustomWidget */
	virtual void SynchronizeProperties() override;

protected:

	UPROPERTY(EditAnywhere)
	FText CustomText;
	
	/** 构建 MyCustomWidget */
	virtual TSharedRef<SWidget> RebuildWidget() override;

	TSharedPtr<STextBlock> MyCustomWidget;
};
