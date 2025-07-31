// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UnderCooked : ModuleRules
{
	public UnderCooked(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"GameplayTags"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"UnderCooked",
			"UnderCooked/Variant_Platforming",
			"UnderCooked/Variant_Combat",
			"UnderCooked/Variant_Combat/AI",
			"UnderCooked/Variant_SideScrolling",
			"UnderCooked/Variant_SideScrolling/Gameplay",
			"UnderCooked/Variant_SideScrolling/AI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
