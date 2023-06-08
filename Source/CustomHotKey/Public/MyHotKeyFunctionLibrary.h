// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyHotKeyFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMHOTKEY_API UMyHotKeyFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static void PrintMessage();
	
};
