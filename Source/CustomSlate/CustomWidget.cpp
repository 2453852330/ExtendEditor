// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomWidget.h"

void UCustomWidget::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	MyCustomWidget.Reset();
}

void UCustomWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	if (MyCustomWidget)
	{
		MyCustomWidget->SetText(CustomText);
	}
}

TSharedRef<SWidget> UCustomWidget::RebuildWidget()
{
	MyCustomWidget = SNew(STextBlock).Text(CustomText);
	return MyCustomWidget.ToSharedRef();
}
