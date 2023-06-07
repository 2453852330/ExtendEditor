#include "ExtendSceneOutlinerStyle.h"

#include "Styling/SlateStyleRegistry.h"

TSharedPtr<FSlateStyleSet> FExtendSceneOutlinerStyle::StyleSet = nullptr;
const FName FExtendSceneOutlinerStyle::StyleSetName = FName("ExtendSceneOutlinerStyle");

void FExtendSceneOutlinerStyle::Initialize()
{
	if (!StyleSet.IsValid())
	{
		StyleSet = CreateSlateStyleSet();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
	}
}

void FExtendSceneOutlinerStyle::UnInitialize()
{
	if (StyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
		StyleSet.Reset();
	}
}

FName FExtendSceneOutlinerStyle::GetStyleSetName()
{
	return StyleSetName;
}

TSharedPtr<FSlateStyleSet> FExtendSceneOutlinerStyle::GetStyleSet()
{
	return StyleSet;
}

TSharedRef<FSlateStyleSet> FExtendSceneOutlinerStyle::CreateSlateStyleSet()
{
	TSharedRef<FSlateStyleSet> SlateStyleSet = MakeShareable(new FSlateStyleSet(StyleSetName));
	
	const FString RootPath = FPaths::ProjectDir() + TEXT("/Resource/");
	SlateStyleSet->SetContentRoot(RootPath);
	
	{
		const FVector2D IconeSize(16.f, 16.f);
		FSlateImageBrush* SlateImageBrush = new FSlateImageBrush(RootPath + TEXT("Lock.png"), IconeSize);
		SlateStyleSet->Set("SceneOutliner.Lock", SlateImageBrush);
	}

	{
		const FVector2D IconeSize(16.f, 16.f);
		FSlateImageBrush* SlateImageBrush = new FSlateImageBrush(RootPath + TEXT("Unlock.png"), IconeSize);
		SlateStyleSet->Set("SceneOutliner.Unlock", SlateImageBrush);
	}

	{
		const FVector2D IconeSize(16.f, 16.f);
		const FCheckBoxStyle SelectionLockToggleButtonStyle =
		   FCheckBoxStyle()
		   .SetCheckBoxType(ESlateCheckBoxType::ToggleButton)
		   .SetPadding(FMargin(10.f))
		   .SetUncheckedImage(FSlateImageBrush(RootPath + TEXT("/Unlock.png"), IconeSize, FLinearColor::White))
		   .SetUncheckedHoveredImage(FSlateImageBrush(RootPath + TEXT("/Unlock.png"), IconeSize, FLinearColor::Blue))
		   .SetUncheckedPressedImage(FSlateImageBrush(RootPath + TEXT("/Unlock.png"), IconeSize, FLinearColor::Red))
		   .SetCheckedImage(FSlateImageBrush(RootPath + TEXT("/Lock.png"), IconeSize, FLinearColor::Yellow))
		   .SetCheckedHoveredImage(FSlateImageBrush(RootPath + TEXT("/Lock.png"), IconeSize, FLinearColor::Black))
		   .SetCheckedPressedImage(FSlateImageBrush(RootPath + TEXT("/Lock.png"), IconeSize, FLinearColor::Gray));

		SlateStyleSet->Set("SceneOutliner.LockToggle", SelectionLockToggleButtonStyle);
	}
	
	return SlateStyleSet;
}
