// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ExtendEditorEditorTarget : TargetRules
{
	public ExtendEditorEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		// add ExtendMenuBase Module to Editor Build Target
		ExtraModuleNames.AddRange( new string[] { 
			"ExtendEditor",
			"ExtendMenuBase",
			"ExtendEditorStyle",
			"ExtendEditorCommand",
			"CustomMessage",
			"CustomSlate"
		} );
	}
}
