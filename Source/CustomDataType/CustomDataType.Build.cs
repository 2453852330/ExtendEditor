﻿using UnrealBuildTool;

public class CustomDataType : ModuleRules
{
	public CustomDataType(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core"
		});
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"CoreUObject","Engine","InputCore"
		});
	}
}