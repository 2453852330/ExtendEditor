#pragma once

#include "AssetTypeActions_Base.h"

class FCustomNormalDistributionActions : public FAssetTypeActions_Base
{
public:
	FCustomNormalDistributionActions(EAssetTypeCategories::Type InAssetCategory);
	
	virtual UClass* GetSupportedClass() const override;
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual uint32 GetCategories() override;

	// Action 就是该资产的右键菜单
	virtual void GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder) override;
	virtual bool HasActions(const TArray<UObject*>& InObjects) const override;

	// 打开AssetEditor
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor) override;

	// 右键重新导入功能实现
	void BindReimporterAction();
	void ExecuteReimport(TArray<TWeakObjectPtr<class UCustomNormalDistribution>> Objects);
	
private:
	EAssetTypeCategories::Type AssetCategory;
};
