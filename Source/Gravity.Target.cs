// Gravity Project - Tom Shinton 2020

using UnrealBuildTool;
using System.Collections.Generic;

public class GravityTarget : TargetRules
{
	public GravityTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Gravity" } );
	}
}
