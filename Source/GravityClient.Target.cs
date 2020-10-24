// Gravity Project - Tom Shinton 2020

using UnrealBuildTool;
using System.Collections.Generic;

public class GravityClientTarget : TargetRules
{
	public GravityClientTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Client;

		ExtraModuleNames.AddRange( new string[] { "Gravity" } );
	}
}
