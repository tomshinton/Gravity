// Gravity Project - Tom Shinton 2020

using UnrealBuildTool;
using System.Collections.Generic;

public class GravityServerTarget : TargetRules
{
	public GravityServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;

		ExtraModuleNames.AddRange( new string[] { "Gravity" } );
	}
}
