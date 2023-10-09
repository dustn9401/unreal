using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealBuildSystemEditorTarget : TargetRules
{
    public UnrealBuildSystemEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V2;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
        ExtraModuleNames.Add("UnrealBuildSystem");
    }
}