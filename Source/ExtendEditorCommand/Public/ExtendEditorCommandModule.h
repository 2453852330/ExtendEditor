﻿#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class FExtendEditorCommandModule : public IModuleInterface
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};


