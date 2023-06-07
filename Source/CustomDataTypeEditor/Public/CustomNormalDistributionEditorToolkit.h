#pragma once

#include "CoreMinimal.h"
#include "CustomNormalDistribution.h"
#include "Toolkits/AssetEditorToolkit.h"

class FCustomNormalDistributionEditorToolkit : public FAssetEditorToolkit
{
public:
	// 外部调用的入口，它可以是任意名字，可以具有任意参数。
	void InitEditor(const TArray<UObject*>& InObjects);

	// 必须实现的虚函数
	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;
	virtual FName GetToolkitFName() const override { return "CustomNormalDistributionEditor"; }
	virtual FText GetBaseToolkitName() const override { return INVTEXT("Custom Normal Distribution Editor"); }
	virtual FString GetWorldCentricTabPrefix() const override { return "Custom Normal Distribution"; }
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return {}; }

	// 自定义函数和NormalDistribution做交互
	float GetMean() const;
	float GetStandardDeviation() const;
	void SetMean(float Mean);
	void SetStandardDeviation(float StandardDeviation);
	
private:
	
	UCustomNormalDistribution* NormalDistribution = nullptr;
};