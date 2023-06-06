#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class FCustomSlateModule : public  IModuleInterface
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

public:
	/** 创建新Button */
	void CreateButtonByStyle();
	void ButtonAction();
	
	/** 运行EUW入口函数 */
	void RunEditorUtilityWidget();

	/** 创建窗口 */
	void SpawnWindow();

	/** 注册Tab */
	void RegisterTab();
	/** 创建Tab */
	void SpawnTab();
	TSharedRef<SDockTab> OnSpawnTab(const FSpawnTabArgs& Args);


	/** 创建 LayoutTab */
	void SpawnLayoutTab();
	TSharedRef<SDockTab> FOnSpawnMainTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> FOnSpawnSubTab(const FSpawnTabArgs& Args, FText Text);
	
	TSharedPtr<FTabManager> TabManager;
	TSharedPtr<FTabManager::FLayout> TabManagerLayout;
};