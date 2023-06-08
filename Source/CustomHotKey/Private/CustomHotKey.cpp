#include "CustomHotKey.h"

#include "AddHotKey.h"

#define LOCTEXT_NAMESPACE "FCustomHotKeyModule"

void FCustomHotKeyModule::StartupModule()
{
    // register style set
    FHotKeyStyle::InitializeStyle();
    // register commands
    FHotKeyCommands::Register();
}

void FCustomHotKeyModule::ShutdownModule()
{
    FHotKeyStyle::UnInitializeStyle();
    FHotKeyCommands::Unregister();
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FCustomHotKeyModule, CustomHotKey)