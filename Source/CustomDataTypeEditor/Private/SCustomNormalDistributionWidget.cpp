// Fill out your copyright notice in the Description page of Project Settings.


#include "SCustomNormalDistributionWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SCustomNormalDistributionWidget::Construct(const FArguments& InArgs)
{
	Mean = InArgs._Mean;
	StandardDeviation = InArgs._StandardDeviation;
	OnMeanChanged = InArgs._OnMeanChanged;
	OnStandardDeviationChanged = InArgs._OnStandardDeviationChanged;
}

int32 SCustomNormalDistributionWidget::OnPaint(
	const FPaintArgs& Args,
	const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect,
	FSlateWindowElementList& OutDrawElements,
	int32 LayerId,
	const FWidgetStyle& InWidgetStyle,
	bool bParentEnabled) const
{
	const int32 NumPoints = 512;
	TArray<FVector2D> Points;
	Points.Reserve(NumPoints);
	// 计算Paint尺寸
	const FTransform2D PointsTransform = GetPointsTransform(AllottedGeometry);
	for (int32 PointIndex = 0; PointIndex < NumPoints; ++PointIndex)
	{
		// 计算公式
		const float X = PointIndex / (NumPoints - 1.0);
		const float D = (X - Mean.Get()) / StandardDeviation.Get();
		const float Y = FMath::Exp(-0.5f * D * D);
		Points.Add(PointsTransform.TransformPoint(FVector2D(X, Y)));
	}
	// 通过点画线
	FSlateDrawElement::MakeLines(OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(), Points);
	return LayerId;
}

FVector2D SCustomNormalDistributionWidget::ComputeDesiredSize(float) const
{
	return FVector2D(200.0, 200.0);
}

FReply SCustomNormalDistributionWidget::OnMouseButtonDown(const FGeometry& AllottedGeometry, const FPointerEvent& MouseEvent)
{
	// if (GEditor && GEditor->CanTransact() && ensure(!GIsTransacting))
	// 启用do/Undo
	if (GEditor &&  ensure(!GIsTransacting))
		GEditor->BeginTransaction(TEXT(""), INVTEXT("Edit Normal Distribution"), nullptr);
	return FReply::Handled().CaptureMouse(SharedThis(this));
}

FReply SCustomNormalDistributionWidget::OnMouseButtonUp(const FGeometry& AllottedGeometry, const FPointerEvent& MouseEvent)
{
	// 关闭do/UnDo
	if (GEditor) GEditor->EndTransaction();
	return FReply::Handled().ReleaseMouseCapture();
}

FReply SCustomNormalDistributionWidget::OnMouseMove(const FGeometry& AllottedGeometry, const FPointerEvent& MouseEvent)
{
	// 检测鼠标捕获模式
	if (!HasMouseCapture()) return FReply::Unhandled();
	const FTransform2D PointsTransform = GetPointsTransform(AllottedGeometry);
	const FVector2D LocalPosition = AllottedGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());
	const FVector2D NormalizedPosition = PointsTransform.Inverse().TransformPoint(LocalPosition);
	// 调用Delegate修改数值
	if (OnMeanChanged.IsBound())
		OnMeanChanged.Execute(NormalizedPosition.X);
	if (OnStandardDeviationChanged.IsBound())
		OnStandardDeviationChanged.Execute(FMath::Max(0.025f, FMath::Lerp(0.025f, 0.25f, NormalizedPosition.Y)));
	return FReply::Handled();
}

FTransform2D SCustomNormalDistributionWidget::GetPointsTransform(const FGeometry& AllottedGeometry) const
{
	const double Margin = 0.05 * AllottedGeometry.GetLocalSize().GetMin();
	const FScale2D Scale((AllottedGeometry.GetLocalSize() - 2.0 * Margin) * FVector2D(1.0, -1.0));
	const FVector2D Translation(Margin, AllottedGeometry.GetLocalSize().Y - Margin);
	return FTransform2D(Scale, Translation);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
