// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "CustomNormalDistributionFactory.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMDATATYPEEDITOR_API UCustomNormalDistributionFactory : public UFactory
{
	GENERATED_BODY()
public:
	UCustomNormalDistributionFactory();
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
