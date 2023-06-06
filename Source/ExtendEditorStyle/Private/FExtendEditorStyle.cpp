
#include "ExtendEditorStyle/Public/FExtendEditorStyle.h"
#include "Modules/ModuleManager.h"
#include "Styling/SlateStyleRegistry.h"

IMPLEMENT_MODULE(FExtendEditorStyle, ExtendEditorStyle)

#define LOCTEXT_NAMESPACE "ExtendEditorStyleNS"

TSharedPtr<FSlateStyleSet> FExtendEditorStyle::StyleSet = nullptr;
const FName FExtendEditorStyle::StyleSetName = FName("ExtendEditorStyleSetName");


void FExtendEditorStyle::StartupModule()
{
	Initialize();
}

void FExtendEditorStyle::ShutdownModule()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
	StyleSet.Reset();
}

FName FExtendEditorStyle::GetStyleSetName()
{
	return StyleSetName;
}

TSharedPtr<FSlateStyleSet> FExtendEditorStyle::GetStyleSet()
{
	return StyleSet;
}

void FExtendEditorStyle::Initialize()
{
	if (!StyleSet.IsValid())
	{
		StyleSet = CreateSlateStyleSet();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
	}
}

TSharedRef<FSlateStyleSet> FExtendEditorStyle::CreateSlateStyleSet()
{
	TSharedRef<FSlateStyleSet> SlateStyleSet = MakeShareable(new FSlateStyleSet(StyleSetName));
	const FString RootPath = FPaths::ProjectDir() + TEXT("/Resource/");
	SlateStyleSet->SetContentRoot(RootPath);
	// 添加Style
	{
		const FVector2D IconSize(16.f, 16.f);
		FSlateImageBrush* SlateImageBrush = 
		new FSlateImageBrush(RootPath + TEXT("Icon128.png"), IconSize);

		SlateStyleSet->Set("AliceTool", SlateImageBrush);
	}
	// use in ExtendEditorCommands
	{
		const FVector2D IconSize(16.f, 16.f);
		FSlateImageBrush* SlateImageBrush = 
		new FSlateImageBrush(RootPath + TEXT("Icon128.png"), IconSize);

		SlateStyleSet->Set("ExtendEditorCommands.PrintLog", SlateImageBrush);
	}
	// use in CustomSlate
	{
		const FVector2D IconSize(16.f, 16.f);
		FSlateImageBrush* SlateImageBrush = 
		new FSlateImageBrush(RootPath + TEXT("Icon128.png"), IconSize);

		SlateStyleSet->Set("CustomSlate", SlateImageBrush);
	}
	
	return SlateStyleSet;
}


#undef LOCTEXT_NAMESPACE
