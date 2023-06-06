// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyClass.generated.h"

UCLASS()
class EDITORCUSTOMIZATION_API AMyClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyClass();


	UPROPERTY(EditAnywhere, Category = "Add Items")
	float A;

	UPROPERTY(EditAnywhere, Category = "Add Items")
	float B;

	UPROPERTY(EditAnywhere, Category = "Result")
	float Sum;
};
