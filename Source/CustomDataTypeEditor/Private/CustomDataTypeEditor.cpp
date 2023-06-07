#include "CustomDataTypeEditor/Public/CustomDataTypeEditor.h"

#include "AssetToolsModule.h"
#include "AssetTypeCategories.h"
#include "CustomNormalDistributionActions.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_MODULE(FCustomDataTypeEditorModule,CustomDataTypeEditor)

void FCustomDataTypeEditorModule::StartupModule()
{
	// 注册新的 Category
	EAssetTypeCategories::Type Category =
		FAssetToolsModule::GetModule().Get().RegisterAdvancedAssetCategory(
			FName(TEXT("Example")), FText::FromString("Example"));
	// 注册 AssetTypeActions
	CustomNormalDistributionActions = MakeShared<FCustomNormalDistributionActions>(Category);
	FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(
		CustomNormalDistributionActions.ToSharedRef());
}

void FCustomDataTypeEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(
			CustomNormalDistributionActions.ToSharedRef());
	}
}
