#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Styling/SlateStyle.h"

class FExtendEditorStyle : public IModuleInterface
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

public:
	
	static TSharedPtr<FSlateStyleSet> StyleSet;
	static const FName StyleSetName;

	
public:

	static EXTENDEDITORSTYLE_API FName GetStyleSetName();
	static EXTENDEDITORSTYLE_API TSharedPtr<FSlateStyleSet> GetStyleSet();
private:
	
	void Initialize();
	TSharedRef<FSlateStyleSet> CreateSlateStyleSet();
};


