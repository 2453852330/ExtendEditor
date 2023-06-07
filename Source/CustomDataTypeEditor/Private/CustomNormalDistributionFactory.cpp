// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomNormalDistributionFactory.h"
#include "CustomDataType/Public/CustomNormalDistribution.h"

UCustomNormalDistributionFactory::UCustomNormalDistributionFactory()
{
	SupportedClass = UCustomNormalDistribution::StaticClass();
	bCreateNew = true;
}

UObject* UCustomNormalDistributionFactory::FactoryCreateNew(
	UClass* Class,
	UObject* InParent,
	FName Name,
	EObjectFlags Flags,
	UObject* Context,
	FFeedbackContext* Warn)
{
	return NewObject<UCustomNormalDistribution>(InParent, Class, Name, Flags, Context);
}
