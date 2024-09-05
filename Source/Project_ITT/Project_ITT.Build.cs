// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Project_ITT : ModuleRules
{
	public Project_ITT(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PrivateIncludePaths.Add("Project_ITT");
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] { "CommonUI", "Slate", "SlateCore", "NiagaraUIRenderer"  });
	}
}
