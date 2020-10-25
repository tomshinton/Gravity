using UnrealBuildTool;

public class ArenaFramework : ModuleRules
{
	public ArenaFramework(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core" });

        PrivateDependencyModuleNames.AddRange(new string[] 
        {
            "Engine",
            "CoreUObject"
        });
		
		PublicIncludePaths.AddRange(new string[] {"Runtime/ArenaFramework/Public"});
		PrivateIncludePaths.AddRange(new string[] {"Runtime/ArenaFramework/Private"});
    }
}
