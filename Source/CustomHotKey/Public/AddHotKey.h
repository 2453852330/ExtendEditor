#pragma once
#include "Styling/SlateStyle.h"

class FHotKeyStyle
{
public:
	static void InitializeStyle();
	static void UnInitializeStyle();

	static TSharedPtr<FSlateStyleSet> CreateSlateStyle();

	static const FName GetStyleSetName();
	static TSharedPtr<FSlateStyleSet> GetStyleSet();
	
private:
	static TSharedPtr<FSlateStyleSet> SlateStyle;
	static const FName SlateStyleName; 
};


class CUSTOMHOTKEY_API FHotKeyCommands : public TCommands<FHotKeyCommands>
{
public:
	FHotKeyCommands();
	virtual void RegisterCommands() override;

	static TSharedRef<FUICommandList> CommandList;
private:
	TSharedPtr<FUICommandInfo> PrintOfBase;
	TSharedPtr<FUICommandInfo> PrintOfStaticFunctionlibrary;
	TSharedPtr<FUICommandInfo> PrintOfBlueprintImplementableEvent;
	TSharedPtr<FUICommandInfo> PrintOfFindFunction;
};

class FHotKeyAction
{
public:
	static void BasePrint();
	static void StaticFunctionLibraryPrint();
	static void PrintOfBlueprintImplementableEvent();
	static void PrintOfFindFunction();
};