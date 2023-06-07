// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomNormalDistributionExporter.h"
#include "CustomNormalDistribution.h"

UCustomNormalDistributionExporter::UCustomNormalDistributionExporter()
{
	
	SupportedClass = UCustomNormalDistribution::StaticClass();
	PreferredFormatIndex = 0;
	FormatExtension.Add(TEXT("cnd"));
	FormatDescription.Add(TEXT("Custom Normal Distribution"));
	bText = true;
}

bool UCustomNormalDistributionExporter::SupportsObject(UObject* Object) const
{
	return (SupportedClass && Object->IsA(SupportedClass));
}

bool UCustomNormalDistributionExporter::ExportText(const FExportObjectInnerContext* Context, UObject* Object,
	const TCHAR* Type, FOutputDevice& Ar, FFeedbackContext* Warn, uint32 PortFlags)
{
	UCustomNormalDistribution* Data = Cast<UCustomNormalDistribution>(Object);

	if (!Data)
	{
		return false;
	}
	
	// 输出内容
	Ar.Log(TEXT("[MySection]\r\n"));
	Ar.Logf(TEXT("Mean=%f\r\n"), Data->Mean);
	Ar.Logf(TEXT("StandardDeviation=%f"), Data->StandardDeviation);
	
	return true;
}