// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "MaterialSpawner.generated.h"

/**
 * 
 */
UCLASS()
class MATERIALRELATED_API UMaterialSpawner : public UEditorUtilityWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void CreateMaterial(const FString& AssetName);

	UFUNCTION(BlueprintCallable)
	void CreateMaterialInstance(UMaterialInterface* ParentMaterial, const FString& AssetName);

	UFUNCTION(BlueprintCallable)
	void SetMaterialParameter();

	UFUNCTION(BlueprintCallable)
	void EditMaterial(UMaterial* Material);
	
	UFUNCTION(BlueprintCallable)
	void AddMaterialFunction(UMaterial* Material);

	UFUNCTION(BlueprintCallable)
	void AddMaterialParameterCollection(UMaterial* Material);
};
