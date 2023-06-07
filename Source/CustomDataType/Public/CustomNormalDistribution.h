// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include <random>
#include "CustomNormalDistribution.generated.h"


UCLASS()
class CUSTOMDATATYPE_API UCustomNormalDistribution : public UObject
{
	GENERATED_BODY()

public:
	UCustomNormalDistribution();

	UFUNCTION(BlueprintCallable)
	float DrawSample();

	UFUNCTION(CallInEditor)
	void LogSample();

public:
	UPROPERTY(EditAnywhere)
	float Mean;

	UPROPERTY(EditAnywhere)
	float StandardDeviation;

	// 新增部分 导入功能,记录源文件路径
#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleAnywhere)
	FString SourceFilePath;
#endif

private:
	std::mt19937 RandomNumberGenerator;
};
