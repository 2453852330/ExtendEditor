﻿
using UnrealBuildTool;

public class ExtendEditorCommand : ModuleRules
{
	public ExtendEditorCommand(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core","CoreUObject","Engine","InputCore"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Slate","ExtendEditorStyle"
		});
	}
}