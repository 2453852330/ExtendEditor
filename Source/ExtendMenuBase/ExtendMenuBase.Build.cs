﻿
using UnrealBuildTool;

public class ExtendMenuBase : ModuleRules
{
	public ExtendMenuBase(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core","CoreUObject","Engine","InputCore"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Slate","SlateCore","ToolMenus",
			"ExtendEditorStyle","ExtendEditorCommand","CustomMessage","UnrealEd"
		});
	}
}