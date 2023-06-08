// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyHotKeyActor.generated.h"


UCLASS()
class CUSTOMHOTKEY_API AMyHotKeyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyHotKeyActor();

	UFUNCTION(BlueprintImplementableEvent)
	void AddTwoInt(int32 A, int32 B);

	UFUNCTION(BlueprintNativeEvent)
	void HelloNativeEvent();

	static void HelloStaticFunction();
};
