// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Exporters/Exporter.h"
#include "CustomNormalDistributionExporter.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMDATATYPEEDITOR_API UCustomNormalDistributionExporter : public UExporter
{
	GENERATED_BODY()
public:
	UCustomNormalDistributionExporter();
	virtual bool SupportsObject(UObject* Object) const override;
	virtual bool ExportText(const FExportObjectInnerContext* Context, UObject* Object, const TCHAR* Type, FOutputDevice& Ar, FFeedbackContext* Warn, uint32 PortFlags) override;
};
