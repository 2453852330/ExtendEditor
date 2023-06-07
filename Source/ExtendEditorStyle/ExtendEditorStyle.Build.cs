
using UnrealBuildTool;

public class ExtendEditorStyle : ModuleRules
{
	public ExtendEditorStyle(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"CoreUObject","Engine","InputCore","SlateCore"
		});
	}
}