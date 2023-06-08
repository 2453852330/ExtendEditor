// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyHotKeyObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CUSTOMHOTKEY_API UMyHotKeyObject : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void AddTwoInt(int32 A,int32 B);
};
