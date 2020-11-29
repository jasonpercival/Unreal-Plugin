// Copyright Epic Games, Inc. All Rights Reserved.

#include "ToolBarPluginCommands.h"

#define LOCTEXT_NAMESPACE "FToolBarPluginModule"

void FToolBarPluginCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "Command Prompt", "Open Command Prompt", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
