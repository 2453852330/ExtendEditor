#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FCustomHotKeyModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    
    typedef TMap< const TSharedPtr< const FUICommandInfo >, FUIAction > FUIBindingMap;
    /** Known contexts in this list.  Each context must be known so we can quickly look up commands from bindings */
    TSet<FName> ContextsInList;
    /** Mapping of command to action */
    FUIBindingMap UICommandBindingMap;
};
