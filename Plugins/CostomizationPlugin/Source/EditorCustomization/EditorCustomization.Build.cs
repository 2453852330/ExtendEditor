using UnrealBuildTool;

public class EditorCustomization : ModuleRules
{
	public EditorCustomization(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core","CoreUObject","Engine","InputCore",
			// 自定义细节面板需要添加以下模块
			"Slate",
			"SlateCore",
			"UnrealEd",
			"PropertyEditor"
		});
	}
}