using UnrealBuildTool;

public class ExtendSceneOutliner : ModuleRules
{
    public ExtendSceneOutliner(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        // bUseRTTI = true;
        
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "SceneOutliner",
                "LevelEditor",
                "UnrealEd"
            }
        );
    }
}