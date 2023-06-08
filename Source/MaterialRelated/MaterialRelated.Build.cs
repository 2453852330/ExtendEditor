using UnrealBuildTool;

public class MaterialRelated : ModuleRules
{
    public MaterialRelated(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "Blutility",
                "UMG",
                "ContentBrowser",
                "AssetTools",
                "UnrealEd"
            }
        );
    }
}