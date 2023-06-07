#pragma once
#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"


class FCustomNormalDistributionActions;

class FCustomDataTypeEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	// 记录注册的 AssetTypeActions 以供模块停用时卸载
	TSharedPtr<FCustomNormalDistributionActions> CustomNormalDistributionActions;
};
