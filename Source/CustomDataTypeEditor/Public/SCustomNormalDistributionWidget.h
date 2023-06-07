// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SLeafWidget.h"

DECLARE_DELEGATE_OneParam(FOnMeanChanged, float /*NewMean*/)
DECLARE_DELEGATE_OneParam(FOnStandardDeviationChanged, float /*NewStandardDeviation*/)

class CUSTOMDATATYPEEDITOR_API SCustomNormalDistributionWidget : public SLeafWidget
{
public:
	SLATE_BEGIN_ARGS(SCustomNormalDistributionWidget)
		: _Mean(0.5f)
		, _StandardDeviation(0.2f)
	{}
	
	SLATE_ATTRIBUTE(float, Mean)
	SLATE_ATTRIBUTE(float, StandardDeviation)
	SLATE_EVENT(FOnMeanChanged, OnMeanChanged)
	SLATE_EVENT(FOnStandardDeviationChanged, OnStandardDeviationChanged)
	
	SLATE_END_ARGS()

public:
	
	void Construct(const FArguments& InArgs);

	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	virtual FVector2D ComputeDesiredSize(float) const override;

	virtual FReply OnMouseButtonDown(const FGeometry& AllottedGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseButtonUp(const FGeometry& AllottedGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseMove(const FGeometry& AllottedGeometry, const FPointerEvent& MouseEvent) override;

private:
	// 提供了Bind函数,从CustomDataType对象中获取值,通过EditorToolkit
	TAttribute<float> Mean;
	TAttribute<float> StandardDeviation;
	// 代理,通过Slate改变值时通知ToolKit去改变CustomDataType中的值
	FOnMeanChanged OnMeanChanged;
	FOnStandardDeviationChanged OnStandardDeviationChanged;

	FTransform2D GetPointsTransform(const FGeometry& AllottedGeometry) const;
};
