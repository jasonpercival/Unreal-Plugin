// Copyright Epic Games, Inc. All Rights Reserved.

#include "ToolBarPlugin.h"
#include "ToolBarPluginStyle.h"
#include "ToolBarPluginCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

static const FName ToolBarPluginTabName("ToolBarPlugin");

#define LOCTEXT_NAMESPACE "FToolBarPluginModule"

void FToolBarPluginModule::StartupModule()
{

	FToolBarPluginStyle::Initialize();
	FToolBarPluginStyle::ReloadTextures();

	FToolBarPluginCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FToolBarPluginCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FToolBarPluginModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FToolBarPluginModule::RegisterMenus));
}

void FToolBarPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FToolBarPluginStyle::Shutdown();

	FToolBarPluginCommands::Unregister();
}

void FToolBarPluginModule::PluginButtonClicked()
{
	FString workingDirectory = FPaths::ProjectDir();

	FProcHandle handle = FPlatformProcess::CreateProc(TEXT("C:\\windows\\system32\\cmd.exe"), 
		nullptr, false, false, false, nullptr, 0, *workingDirectory, nullptr);

	if (handle.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Successfully opened command prompt."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Error Launching command prompt."));
		FText DialogText = FText::FromString("Error Launching Command Prompt");
		FMessageDialog::Open(EAppMsgType::Ok, DialogText);
	}

}

void FToolBarPluginModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FToolBarPluginCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FToolBarPluginCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FToolBarPluginModule, ToolBarPlugin)