
using UnrealBuildTool;

public class ExtendEditorCommand : ModuleRules
{
	public ExtendEditorCommand(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"CoreUObject","Engine","InputCore",
			"Slate","ExtendEditorStyle"
		});
	}
}