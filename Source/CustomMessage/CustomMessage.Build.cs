
using UnrealBuildTool;

public class CustomMessage : ModuleRules
{
	public CustomMessage(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"UnrealEd","CoreUObject","Engine","InputCore"
		});
	}
}