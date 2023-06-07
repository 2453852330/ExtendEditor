using UnrealBuildTool;

public class CustomDataTypeEditor : ModuleRules
{
	public CustomDataTypeEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"CustomDataType","Slate","SlateCore","UnrealEd",
			"CoreUObject","Engine","InputCore"
		});
	}
}