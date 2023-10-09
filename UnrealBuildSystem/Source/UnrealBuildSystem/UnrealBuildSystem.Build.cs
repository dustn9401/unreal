using UnrealBuildTool;

public class UnrealBuildSystem : ModuleRules 
{
	public UnrealBuildSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine", "InputCore"});
        PrivateDependencyModuleNames.AddRange(new string[] {});
	}
}