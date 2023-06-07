using UnrealBuildTool;

public class CustomSlate : ModuleRules
{
	public CustomSlate(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"CoreUObject","Engine","InputCore",
			"ExtendEditorStyle","SlateCore","ToolMenus","Slate","Blutility","UMGEditor","UnrealEd","UMG"
		});
	}
}