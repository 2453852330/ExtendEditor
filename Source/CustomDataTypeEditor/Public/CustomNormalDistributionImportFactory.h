// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// 重新导入
#include "EditorReimportHandler.h"
#include "Factories/Factory.h"
#include "CustomNormalDistributionImportFactory.generated.h"

/**
 * 
 */
UCLASS()
// 
class CUSTOMDATATYPEEDITOR_API UCustomNormalDistributionImportFactory : public UFactory , public FReimportHandler
{
	GENERATED_BODY()
public:
	UCustomNormalDistributionImportFactory();
	// 重载函数: 导入功能
	virtual UObject* FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const TCHAR*& Buffer, const TCHAR* BufferEnd, FFeedbackContext* Warn) override;
	virtual bool FactoryCanImport(const FString& Filename) override;
	// 自定义函数
	FString GetValueFromFile(const TCHAR*& Buffer, FString SectionName, FString VarName);

	// 新增继承类 FReimportHandler
	// 自定义函数 新增 Reimporter 虚函数实现 
	virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;
	virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;
	virtual EReimportResult::Type Reimport(UObject* Obj) override;
};
