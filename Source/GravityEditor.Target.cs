// Gravity Project - Tom Shinton 2020

using UnrealBuildTool;
using System.Collections.Generic;

public class GravityEditorTarget : TargetRules
{
	public GravityEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "Gravity" } );
	}
}
