#include "EditorCustomization.h"

#include "CustomType.h"
#include "MyClass.h"
#include "MyClassCustomization.h"
#include "MyStructCustomization.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_MODULE(FEditorCustomizationModule, EditorCustomization)

#define LOCTEXT_NAMESPACE "EditorCustomizationNS"

void FEditorCustomizationModule::StartupModule()
{
	// 加载 PropertyEditor 模块
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	//
	// 注册自定义属性，绑定结构名与自定义类
	PropertyModule.RegisterCustomPropertyTypeLayout(
		// 结构名
		FMyStruct::StaticStruct()->GetFName(),
		// 自定义类实例
		FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FMyStructCustomization::MakeInstance));

	// 注册自定义细节面板的类
	PropertyModule.RegisterCustomClassLayout(
	AMyClass::StaticClass()->GetFName(),
	FOnGetDetailCustomizationInstance::CreateStatic(&FMyClassCustomization::MakeInstance));
	
	PropertyModule.NotifyCustomizationModuleChanged();
}

void FEditorCustomizationModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		// 注销自定义细节面板结构体
		PropertyModule.UnregisterCustomPropertyTypeLayout("MyStruct");
		// 注销自定义细节面板类
		PropertyModule.UnregisterCustomClassLayout("MyClass");
		
		PropertyModule.NotifyCustomizationModuleChanged();
	}
}

#undef LOCTEXT_NAMESPACE
