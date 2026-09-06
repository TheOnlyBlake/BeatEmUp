// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BeatEmUp : ModuleRules
{
	public BeatEmUp(ReadOnlyTargetRules Target) : base(Target)
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
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"BeatEmUp",
			"BeatEmUp/Variant_Platforming",
			"BeatEmUp/Variant_Platforming/Animation",
			"BeatEmUp/Variant_Combat",
			"BeatEmUp/Variant_Combat/AI",
			"BeatEmUp/Variant_Combat/Animation",
			"BeatEmUp/Variant_Combat/Gameplay",
			"BeatEmUp/Variant_Combat/Interfaces",
			"BeatEmUp/Variant_Combat/UI",
			"BeatEmUp/Variant_SideScrolling",
			"BeatEmUp/Variant_SideScrolling/AI",
			"BeatEmUp/Variant_SideScrolling/Gameplay",
			"BeatEmUp/Variant_SideScrolling/Interfaces",
			"BeatEmUp/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
