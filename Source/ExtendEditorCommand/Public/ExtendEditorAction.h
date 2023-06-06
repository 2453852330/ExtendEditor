#pragma once
#include "Framework/Commands/Commands.h"
#include "Framework/Commands/UICommandList.h"


class EXTENDEDITORCOMMAND_API FExtendEditorCommands : public TCommands<FExtendEditorCommands>
{
public:
	FExtendEditorCommands();
	virtual void RegisterCommands() override;
	
	// FUICommandList成对地映射 UICommandInfo与其 Action
	static TSharedRef< FUICommandList > CommandList;
	
	
	// UICommandInfo List
	// FUICommandInfo储存 Command样式信息
	TSharedPtr< FUICommandInfo > PrintLog;
};

/**
 * Action合集类
 */
class FExtendEditorActionCallbacks
{
public:
	// Action List
	static void PrintLog();
	
};