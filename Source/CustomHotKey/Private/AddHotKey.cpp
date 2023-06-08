#include "AddHotKey.h"

#include "LevelEditor.h"
#include "MyHotKeyActor.h"
#include "MyHotKeyFunctionLibrary.h"
#include "MyHotKeyObject.h"
#include "Styling/SlateStyleRegistry.h"

TSharedPtr<FSlateStyleSet>  FHotKeyStyle::SlateStyle = nullptr;
const FName FHotKeyStyle::SlateStyleName = FName("SlateStyleAddHotKey"); 

void FHotKeyStyle::InitializeStyle()
{
	if (!SlateStyle.IsValid())
	{
		SlateStyle = CreateSlateStyle();
		FSlateStyleRegistry::RegisterSlateStyle(*SlateStyle);
	}
}

void FHotKeyStyle::UnInitializeStyle()
{
	if (SlateStyle.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*SlateStyle);
		SlateStyle.Reset();
	}
}

TSharedPtr<FSlateStyleSet> FHotKeyStyle::CreateSlateStyle()
{
	TSharedPtr<FSlateStyleSet> CreatedStyleSet = MakeShared<FSlateStyleSet>(SlateStyleName);
	
	const FString RootPath = FPaths::ProjectDir() + TEXT("/Resource/");
	CreatedStyleSet->SetContentRoot(RootPath);
	
	// 资源配置列表
	{
		const FVector2D IconeSize(16.f, 16.f);
		FSlateImageBrush* SlateImageBrush = 
			new FSlateImageBrush(RootPath + TEXT("Icon128.png"), IconeSize);

		CreatedStyleSet->Set("HotKeyCommands.PrintOfBase", SlateImageBrush);
	}

	// 新增 FSlateImageBrush
	{
		const FVector2D IconeSize(16.f, 16.f);
		FSlateImageBrush* SlateImageBrush = 
			new FSlateImageBrush(RootPath + TEXT("Icon128.png"), IconeSize);
		CreatedStyleSet->Set("HotKeyCommands.PrintOfStaticFunctionlibrary", SlateImageBrush);
	}

	// 新增 FSlateImageBrush
	{
		const FVector2D IconeSize(16.f, 16.f);
		FSlateImageBrush* SlateImageBrush = 
			new FSlateImageBrush(RootPath + TEXT("Icon128.png"), IconeSize);
		CreatedStyleSet->Set("HotKeyCommands.PrintOfBlueprintImplementableEvent", SlateImageBrush);
	}

	// 新增 FSlateImageBrush
	{
		const FVector2D IconeSize(16.f, 16.f);
		FSlateImageBrush* SlateImageBrush = 
			new FSlateImageBrush(RootPath + TEXT("Icon128.png"), IconeSize);
		CreatedStyleSet->Set("HotKeyCommands.PrintOfFindFunction", SlateImageBrush);
	}
	return CreatedStyleSet;
}

const FName FHotKeyStyle::GetStyleSetName()
{
	return SlateStyleName;
}

TSharedPtr<FSlateStyleSet> FHotKeyStyle::GetStyleSet()
{
	return SlateStyle;
}
/*************************************** Command *************************************/

#define LOCTEXT_NAMESPACE "HotKeyCommandsNS"

TSharedRef<FUICommandList> FHotKeyCommands::CommandList = MakeShareable(new FUICommandList);

// SlateStyleSet如何和CommandInfo进行匹配
// 以"HotKeyCommands.PrintOfBase"为例
// 注册TCommands时传递第一级名称:HotKeyCommands
// 注册UI_COMMAND()时传递第二级名称:PrintOfBase

FHotKeyCommands::FHotKeyCommands()
	:TCommands(
		TEXT("HotKeyCommands"),
		LOCTEXT("PrintOfBaseKey","print of base's tooltip"),
		NAME_None,
		FHotKeyStyle::GetStyleSetName())
{
	
}

void FHotKeyCommands::RegisterCommands()
{
	// 对 FUICommandInfo 执行注册的列表
	{
		// 配置 FInputChord
		FInputChord InputChord(EKeys::Q, EModifierKey::Alt | EModifierKey::Shift);
		
		// 注册 FUICommandInfo
		UI_COMMAND(
			PrintOfBase,  // the ui command info
			"Print Of Base", // name
			"Basic methods for custom hot key", // tooltip
			EUserInterfaceActionType::Button, // type
			InputChord // key
		)
		// bind command to function
		CommandList->MapAction(
			PrintOfBase, 
			FExecuteAction::CreateStatic(&FHotKeyAction::BasePrint)
		);
	}


	// 新增 FUICommandInfo 注册
	{
		FInputChord InputChord(EKeys::W, EModifierKey::Alt | EModifierKey::Shift);
		
		UI_COMMAND(
			PrintOfStaticFunctionlibrary,
			"Print Of Static Function Library",
			"Static function library for custom hot key",
			EUserInterfaceActionType::Button,
			InputChord
		)
		
		CommandList->MapAction(
			PrintOfStaticFunctionlibrary, 
			FExecuteAction::CreateStatic(&FHotKeyAction::StaticFunctionLibraryPrint)
		);
	}


	// 对 FUICommandInfo 执行注册的列表
	{
		// 配置 FInputChord
		FInputChord InputChord(EKeys::E, EModifierKey::Alt | EModifierKey::Shift);
		
		// 注册 FUICommandInfo
		UI_COMMAND(
			PrintOfBlueprintImplementableEvent,  // the ui command info
			"Print Of BlueprintImplementableEvent", // name
			"Basic methods for custom hot key", // tooltip
			EUserInterfaceActionType::Button, // type
			InputChord // key
		)
		// bind command to function
		CommandList->MapAction(
			PrintOfBlueprintImplementableEvent, 
			FExecuteAction::CreateStatic(&FHotKeyAction::PrintOfBlueprintImplementableEvent)
		);
	}

	// 对 FUICommandInfo 执行注册的列表
	{
		// 配置 FInputChord
		// R 已经被引用查看器占用
		FInputChord InputChord(EKeys::T, EModifierKey::Alt | EModifierKey::Shift);
		
		// 注册 FUICommandInfo
		UI_COMMAND(
			PrintOfFindFunction,  // the ui command info
			"Print Of FindFunction", // name
			"Basic methods for custom hot key", // tooltip
			EUserInterfaceActionType::Button, // type
			InputChord // key
		)
		// bind command to function
		CommandList->MapAction(
			PrintOfFindFunction, 
			FExecuteAction::CreateStatic(&FHotKeyAction::PrintOfFindFunction)
		);
	}
	
	// 获取全局通用关卡编辑器命令列表
	FLevelEditorModule& LevelEditorModule = 
		FModuleManager::LoadModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
	TSharedRef<FUICommandList> ExistingLevelCommands = 
		LevelEditorModule.GetGlobalLevelEditorActions();
	
	// 添加自定义的CommandList到全局
	ExistingLevelCommands->Append(CommandList);
}

#undef LOCTEXT_NAMESPACE

/*************************************** Bind Action *************************************/

void FHotKeyAction::BasePrint()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
		TEXT("BasePrint is triggered. (Shift + Alt + Q)"));

	UE_LOG(LogTemp, Warning, TEXT("BasePrint is triggered.(Shift + Alt + Q)"))
}

void FHotKeyAction::StaticFunctionLibraryPrint()
{
	UMyHotKeyFunctionLibrary::PrintMessage();
}

void FHotKeyAction::PrintOfBlueprintImplementableEvent()
{
	// 这种方式调用的是C++版本的函数;
	{
		// // 注意Load蓝图类需要加_C后缀
		// UClass * AMyHotKeyActorClass = LoadClass<AMyHotKeyActor>(nullptr,TEXT("Blueprint'/Game/BP_MyHotKeyActor.BP_MyHotKeyActor_C'"));
		// UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:Load BP Class: %s"),__FUNCTIONW__,__LINE__,AMyHotKeyActorClass?TEXT("Success"):TEXT("Failed"));
		//
		// // 通过Class生成对象
		// if (AMyHotKeyActorClass)
		// {
		// 	AMyHotKeyActor * HotKeyActor = NewObject<AMyHotKeyActor>(GetTransientPackage(),AMyHotKeyActorClass);
		// 	UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:NewObject Of HotKeyActor: %s"),__FUNCTIONW__,__LINE__,HotKeyActor?TEXT("Success"):TEXT("Failed"));
		// 	if (HotKeyActor)
		// 	{
		// 		// 调用函数
		// 		HotKeyActor->AddTwoInt(FMath::RandRange(0,10),FMath::RandRange(0,10));
		// 	}
		// }
	}

	// UE5
	{
		// UObject* MyObject = UEditorAssetLibrary::LoadAsset(FString(TEXT(
		// "Blueprint'/Game/HotKey/BP_MyHotKeyObjectBlueprint.BP_MyHotKeyObjectBlueprint'")));
		//
		// if(MyObject)
		// {
		// 	UBlueprint* MyBlueprint = Cast<UBlueprint>(MyObject);
		//
		// 	if(MyBlueprint)
		// 	{
		// 		UMyHotKeyObject* MyHotKeyObject = 
		// 			NewObject<UMyHotKeyObject>(GetTransientPackage(), MyBlueprint->GeneratedClass);
		//
		// 		if(MyHotKeyObject)
		// 		{
		// 			int Result = MyHotKeyObject->AddInt(4, 96);
		// 		
		// 			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, 
		// 				FString::Printf(TEXT("AddInt Result = %d. (Shift + Alt + W)"), Result));
		// 		
		// 			UE_LOG(LogTemp, Warning, 
		// 				TEXT("AddInt Result = %d. (Shift + Alt + W)"), Result)
		// 		}
		// 	}
		// }
	}

	// 调用Actor,不支持
	{
		UObject * HotKeyObject = LoadObject<UObject>(nullptr,TEXT("Blueprint'/Game/BP_MyHotKeyActor.BP_MyHotKeyActor_C'"));
		UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:Load Object Result: %s"),__FUNCTIONW__,__LINE__,HotKeyObject?TEXT("Success"):TEXT("Failed"));
		
		if (HotKeyObject)
		{
			// Cast Failed
			UBlueprint * BPObject = Cast<UBlueprint>(HotKeyObject);
			UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:Cast to BP Object Result: %s"),__FUNCTIONW__,__LINE__,BPObject?TEXT("Success"):TEXT("Failed"));
		
			if (BPObject)
			{
				AMyHotKeyActor * HotKeyActor = NewObject<AMyHotKeyActor>(GetTransientPackage(),BPObject->GeneratedClass);
				UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:New HotKeyActor Result: %s"),__FUNCTIONW__,__LINE__,HotKeyActor?TEXT("Success"):TEXT("Failed"));
				if (HotKeyActor)
				{
					UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:Add Two Int Func Called"),__FUNCTIONW__,__LINE__);
					HotKeyActor->AddTwoInt(5,6);
				}
			}

			// Cast Success
			UClass * BPClass = Cast<UClass>(HotKeyObject);
			UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:Cast to BP Class Result: %s"),__FUNCTIONW__,__LINE__,BPClass?TEXT("Success"):TEXT("Failed"));
			if (BPClass)
			{
				AMyHotKeyActor * HotKeyActor = NewObject<AMyHotKeyActor>(GetTransientPackage(),BPClass);
				UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:New HotKeyActor Result: %s"),__FUNCTIONW__,__LINE__,HotKeyActor?TEXT("Success"):TEXT("Failed"));
				if (HotKeyActor)
				{
					
					UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:New HotKeyActor Call Functions Start"),__FUNCTIONW__,__LINE__);
					// Called,But Not Run -> ERROR
					HotKeyActor->AddTwoInt(5,6);
					// Test BlueprintNativeEvent -> ERROR
					HotKeyActor->HelloNativeEvent();
					// test static function -> OK
					AMyHotKeyActor::HelloStaticFunction();
					
					UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:New HotKeyActor Call Functions End"),__FUNCTIONW__,__LINE__);
				}
			}
		}
	}

	
	UE_LOG(LogTemp,Warning,TEXT("----------------------------------------------------------------------------"));

	
	// 调用Object可以成功
	{
		// Blueprint'/Game/BP_MyHotKeyObject.BP_MyHotKeyObject'
		UObject * HotKeyObject = LoadObject<UObject>(nullptr,TEXT("Blueprint'/Game/BP_MyHotKeyObject.BP_MyHotKeyObject'"));
		UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:Load Object Result: %s"),__FUNCTIONW__,__LINE__,HotKeyObject?TEXT("Success"):TEXT("Failed"));
		
		if (HotKeyObject)
		{
			// YES
			UBlueprint * BPObject = Cast<UBlueprint>(HotKeyObject);
			UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:Cast to BP Object Result: %s"),__FUNCTIONW__,__LINE__,BPObject?TEXT("Success"):TEXT("Failed"));
		
			if (BPObject)
			{
				UMyHotKeyObject * HotKey = NewObject<UMyHotKeyObject>(GetTransientPackage(),BPObject->GeneratedClass);
				UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:New HotKeyActor Result: %s"),__FUNCTIONW__,__LINE__,HotKey?TEXT("Success"):TEXT("Failed"));
				if (HotKey)
				{
					HotKey->AddTwoInt(5,6);
				}
			}
			
			// NO
			UClass * BPClass = Cast<UClass>(HotKeyObject);
			UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:Cast to Class Result:%s"),__FUNCTIONW__,__LINE__,BPClass?TEXT("Success"):TEXT("Failed"));
			if (BPClass)
			{
				UMyHotKeyObject * HotKey = NewObject<UMyHotKeyObject>(GetTransientPackage(),BPClass);
				UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:New HotKeyActor Result: %s"),__FUNCTIONW__,__LINE__,HotKey?TEXT("Success"):TEXT("Failed"));
				if (HotKey)
				{
					HotKey->AddTwoInt(5,6);
				}
			}
		}
	}
}

void FHotKeyAction::PrintOfFindFunction()
{
	// UE5
	{
		// UObject* MyObject = UEditorAssetLibrary::LoadAsset(
		// FString(TEXT("Blueprint'/Game/HotKey/BP_MyHotKeyObjectBlueprint.BP_MyHotKeyObjectBlueprint'")));
		//
		// if(MyObject)
		// {
		// 	UBlueprint* MyBlueprint = Cast<UBlueprint>(MyObject);
		//
		// 	if(MyBlueprint)
		// 	{
		// 		UMyHotKeyObject* MyHotKeyObject = 
		// 			NewObject<UMyHotKeyObject>(GetTransientPackage(), MyBlueprint->GeneratedClass);
		//
		// 		// 查找并使用无参函数 FunctionToFind
		// 		if(MyHotKeyObject)
		// 		{
		// 			UFunction* MyFunction = 
		// 				MyHotKeyObject->FindFunction(FName("FunctionToFind"));
		//
		// 			if(MyFunction)
		// 			{
		// 				// 因为没有输入参数和输出，ProcessEvent 第二参数传空
		// 				MyHotKeyObject->ProcessEvent(MyFunction, nullptr);
		// 			}
		// 		}
		//
		// 		// 查找并使用具参函数 ParamFunctionToFind
		// 		if(MyHotKeyObject)
		// 		{
		// 			UFunction* MyFunction = 
		// 				MyHotKeyObject->FindFunction(FName("ParamFunctionToFind"));
		//
		// 			if(MyFunction)
		// 			{
		// 				// 使用结构体传递参数，如果有输出值，则结构体末位成员接受输出
		// 				struct Params
		// 				{
		// 					int A;
		// 					int B;
		// 					int AddResult;
		// 				};
		//
		// 				Params Parameters;
		// 				Parameters.A = 3;
		// 				Parameters.B = 10;
		// 			
		// 				// 需要提供输入参数和输出，提供自定义结构体
		// 				MyHotKeyObject->ProcessEvent(MyFunction, &Parameters);
		//
		// 				// 结构体末位成员获得输出值，尝试取出输出的值
		// 				int Result = Parameters.AddResult;
		//
		// 				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, 
		// 					FString::Printf(TEXT("ParamFunctionToFind Result = %d"), Result));
		//
		// 				UE_LOG(LogTemp, Warning, TEXT("ParamFunctionToFind Result = %d"), Result)
		// 			}
		// 		}
		// 	}
		// }
	}

	// UE4
	{
		UClass * LoadedClass = LoadClass<UMyHotKeyObject>(nullptr,TEXT("Blueprint'/Game/BP_MyHotKeyObject.BP_MyHotKeyObject_C'"));
		UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:Load Hot Key Object Class Result:%s"),__FUNCTIONW__,__LINE__,LoadedClass?TEXT("Success"):TEXT("Failed"));
		if (LoadedClass)
		{
			UMyHotKeyObject * HotKeyObject = NewObject<UMyHotKeyObject>(GetTransientPackage(),LoadedClass);
			UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:Create HotKeyObject Result : %s"),__FUNCTIONW__,__LINE__,HotKeyObject?TEXT("Success"):TEXT("Failed"));
			if (HotKeyObject)
			{
				UFunction * Func1 = HotKeyObject->FindFunction(TEXT("FunctionToFind"));
				UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:Find [FunctionToFind] Result:%s"),__FUNCTIONW__,__LINE__,Func1?TEXT("Success"):TEXT("Failed"));
				HotKeyObject->ProcessEvent(Func1,nullptr);

				UFunction * Func2 = HotKeyObject->FindFunction(TEXT("ParamFuntionToFind"));
				UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:Find [ParamFuntionToFind] Result:%s"),__FUNCTIONW__,__LINE__,Func2?TEXT("Success"):TEXT("Failed"));
				struct ParamInfo
				{
					int32 A;
					int32 B;
					int32 Return;
				};
				ParamInfo info;
				info.A = FMath::RandRange(0,10);
				info.B = FMath::RandRange(0,10);
				HotKeyObject->ProcessEvent(Func2,&info);
				UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:ParamFuntionToFind Called : %d + %d = %d"),__FUNCTIONW__,__LINE__,info.A,info.B,info.Return);
			}
		}
	}
}
