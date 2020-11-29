// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "ToolBarPluginStyle.h"

class FToolBarPluginCommands : public TCommands<FToolBarPluginCommands>
{
public:

	FToolBarPluginCommands()
		: TCommands<FToolBarPluginCommands>(TEXT("ToolBarPlugin"), NSLOCTEXT("Contexts", "ToolBarPlugin", "ToolBarPlugin Plugin"), NAME_None, FToolBarPluginStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
