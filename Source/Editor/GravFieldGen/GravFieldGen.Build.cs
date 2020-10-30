using UnrealBuildTool;

public class GravFieldGen : ModuleRules
{
	public GravFieldGen(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core" });

        PrivateDependencyModuleNames.AddRange(new string[] 
        {
			"ArenaFramework",
			"EditorStyle",
            "Engine",
            "CoreUObject",
			"Slate",
			"SlateCore"
        });
		
		PublicIncludePaths.AddRange(new string[] {"Editor/GravFieldGen/Public"});
		PrivateIncludePaths.AddRange(new string[] {"Editor/GravFieldGen/Private"});
    }
}
