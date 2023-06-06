
#include "ExtendEditorCommand/Public/ExtendEditorCommandModule.h"
#include "ExtendEditorCommand/Public/ExtendEditorAction.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_MODULE(FExtendEditorCommandModule,ExtendEditorCommand)


void FExtendEditorCommandModule::StartupModule()
{
	// 这种方式会崩溃,因为并没有FExtendEditorCommands的创建
	// FExtendEditorCommands::Get().Register();

	// 下面的静态方式会检测是否创建FExtendEditorCommands
	FExtendEditorCommands::Register();	
}

void FExtendEditorCommandModule::ShutdownModule()
{
	FExtendEditorCommands::Unregister();
}
