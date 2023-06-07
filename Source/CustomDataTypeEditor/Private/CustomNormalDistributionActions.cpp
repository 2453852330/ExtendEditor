#include "CustomNormalDistributionActions.h"

#include "AssetSelection.h"
#include "CustomNormalDistribution.h"
#include "CustomNormalDistributionEditorToolkit.h"
#include "EditorReimportHandler.h"

FCustomNormalDistributionActions::FCustomNormalDistributionActions(EAssetTypeCategories::Type InAssetCategory)
	: AssetCategory(InAssetCategory)
{
}

UClass* FCustomNormalDistributionActions::GetSupportedClass() const
{
	return UCustomNormalDistribution::StaticClass();
}

FText FCustomNormalDistributionActions::GetName() const
{
	return INVTEXT("Custom Normal Distribution");
}

FColor FCustomNormalDistributionActions::GetTypeColor() const
{
	return FColor::Orange;
}

uint32 FCustomNormalDistributionActions::GetCategories()
{
	return AssetCategory;
}

void FCustomNormalDistributionActions::GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder)
{
	FAssetTypeActions_Base::GetActions(InObjects, MenuBuilder);
	
	MenuBuilder.AddMenuEntry(
		FText::FromString("Custom Action"),
		FText::FromString("This is a custom action"),
		FSlateIcon(),
		FUIAction()
		);

	MenuBuilder.AddMenuEntry(
		FText::FromString("Reimporter"),
		FText::FromString("Reimporter data from file"),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateRaw(this,&FCustomNormalDistributionActions::BindReimporterAction)
		));
}

// HasActions() 必须返回 true 以使 GetActions() 有效
bool FCustomNormalDistributionActions::HasActions(const TArray<UObject*>& InObjects) const
{
	return true;
}

void FCustomNormalDistributionActions::OpenAssetEditor(
	const TArray<UObject*>& InObjects,
	TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	// 调用 FAssetEditorToolkit 子类的 InitEditor 创建Editor
	MakeShared<FCustomNormalDistributionEditorToolkit>()->InitEditor(InObjects);
}


/*************************************** 重新导入 *************************************/
void FCustomNormalDistributionActions::BindReimporterAction()
{
	// 获取选择的Asset
	TArray<FAssetData> SelectedAssets;
	AssetSelectionUtils::GetSelectedAssets(SelectedAssets);
	UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:Select %d Assets"),__FUNCTIONW__,__LINE__,SelectedAssets.Num());
	// 检测类型
	TArray<TWeakObjectPtr<UCustomNormalDistribution>> FindData;
	FindData.Reserve(SelectedAssets.Num());
	for (const FAssetData & it : SelectedAssets)
	{
		UCustomNormalDistribution * CND =Cast<UCustomNormalDistribution>(it.GetAsset());
		if (CND)
		{
			FindData.Add(CND);
		}
	}
	// 调用重新导入
	if (FindData.Num())
	{
		ExecuteReimport(FindData);
	}
}

void FCustomNormalDistributionActions::ExecuteReimport(TArray<TWeakObjectPtr<UCustomNormalDistribution>> Objects)
{
	for (auto ObjIt = Objects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto Object = (*ObjIt).Get();
		if (Object)
		{
			FReimportManager::Instance()->Reimport(Object, /*bAskForNewFileIfMissing=*/true);
		}
	}
}
