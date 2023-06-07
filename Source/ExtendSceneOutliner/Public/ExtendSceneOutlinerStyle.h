#pragma once
#include "Styling/SlateStyle.h"

class FExtendSceneOutlinerStyle
{
public:
	// 模块启动时，注册该样式集到中央管理库
	static void Initialize();
	static void UnInitialize();

	static FName GetStyleSetName();

	static TSharedPtr<FSlateStyleSet> GetStyleSet();
	
private:
	
	static TSharedRef<FSlateStyleSet> CreateSlateStyleSet();

private:
	
	static TSharedPtr<FSlateStyleSet> StyleSet;
	static const FName StyleSetName;
};
