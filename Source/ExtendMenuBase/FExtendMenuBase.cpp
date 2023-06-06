
#include "FExtendMenuBase.h"

#include "ContentBrowserModule.h"
#include "ExtendEditorAction.h"
#include "ExtendEditorCommandModule.h"
#include "FExtendEditorStyle.h"
#include "LevelEditor.h"
#include "MessageClass.h"
#include "ToolMenus.h"
#include "Dialogs/CustomDialog.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Misc/MessageDialog.h"
#include "Modules/ModuleManager.h"
#include "Widgets/Notifications/SNotificationList.h"

#define LOCTEXT_NAMESPACE "ExtendMenuBaseNS"

const FText Title = LOCTEXT("TitleKey","Module Loader");

IMPLEMENT_MODULE(FExtendMenuBase,ExtendMenuBase);

DEFINE_LOG_CATEGORY(MyLog)

void FExtendMenuBase::StartupModule()
{
	// FMessageDialog::Open(EAppMsgType::Ok,LOCTEXT("Key01","ExtendMenuBase Module StartUp"),&Title);
	
	ExtendMenuByFExtend();
	ExtendContentBrowserByFExtend();
	ExtendViewportByFExtend();

	// 由FLevelEditorModule管理的拓展入口
	FLevelEditorModule& LevelEditorModule = 
	FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	LevelEditorModule.OnLevelEditorCreated().AddRaw(this, &FExtendMenuBase::OnLevelEditorCreatedEvent);

	// Style Set
	StyleSample();

	// 确保FExtendEditorCommandModule已加载
	FModuleManager::LoadModuleChecked<FExtendEditorCommandModule>("ExtendEditorCommand");
	CommandSample();
}

void FExtendMenuBase::ShutdownModule()
{
}

void FExtendMenuBase::ExtendMenuByFExtend()
{
	// 1.new FExtender
	TSharedPtr<FExtender> MainMenuExtender = MakeShareable(new FExtender);

	// 2.set FExtender
	// 分别对应主菜单按钮下的子按钮，主菜单按钮以及ToolBar上的按钮。
	// MainMenuExtender->AddMenuBarExtension();
	// MainMenuExtender->AddMenuExtension();
	
	// 起始于此处
	// 01
	MainMenuExtender->AddMenuExtension(
		"HelpApplication",		// 用于定位的ExtensionHook名称
		EExtensionHook::After,	        // 应添加到的具体位置(该Hook之前还是之后)
		nullptr,			// CommandList我们先暂时缺省
		FMenuExtensionDelegate::CreateRaw(
		this, &FExtendMenuBase::MakeExistingMainMenuEntry)	// 绑定制作按钮的代理函数
		);
	// 02
	MainMenuExtender->AddMenuBarExtension(
		"Help",
		EExtensionHook::After,
		nullptr,
		FMenuBarExtensionDelegate::CreateRaw(this,&FExtendMenuBase::MakeNewMenuBarEntry)
		);
	
	// 3.add FExtender to FExtensibilityManager
	FLevelEditorModule & LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	TSharedPtr<FExtensibilityManager> MenuExtensibilityManager = LevelEditorModule.GetMenuExtensibilityManager();
	MenuExtensibilityManager->AddExtender(MainMenuExtender);
}

void FExtendMenuBase::MakeExistingMainMenuEntry(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(
		FText::FromString("Existing Hook Button"),	        // 按钮名称
		FText::FromString("This is a existing hook extend"),	// 按钮提示
		FSlateIcon(),	            // 我们可以为按钮添加图标，这里暂时缺省
		FUIAction(FExecuteAction::CreateRaw(
		this, &FExtendMenuBase::ExistingMainMenuEntryAction))// 绑定执行按钮的代理函数
		);
}

void FExtendMenuBase::ExistingMainMenuEntryAction()
{
	UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:ExistingMainMenuEntryAction Clicked"),__FUNCTIONW__,__LINE__);

	UE_LOG(MyLog,Warning,TEXT("[%s::%d]:Custom Log Category: MyLog Called"),__FUNCTIONW__,__LINE__);
}

void FExtendMenuBase::MakeNewMenuBarEntry(FMenuBarBuilder& MenuBarBuilder)
{
	MenuBarBuilder.AddPullDownMenu(						// 添加下拉菜单按钮
		FText::FromString("New Menu"),					// 该按钮名称
		FText::FromString("This is a new menu bar button"),
		FNewMenuDelegate::CreateRaw(this, &FExtendMenuBase::MakeNewMainMenuEntry),
		"New Menu Hook"					                // 该按钮的ExtensionHook
		);
}

void FExtendMenuBase::MakeNewMainMenuEntry(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.BeginSection("Section 1", FText::FromString("Section 1"));	// 设置Section

	MenuBuilder.AddMenuEntry(
	FText::FromString("New Menu Button"),
	FText::FromString("This is a new menu button"),
	FSlateIcon(),
	FUIAction(FExecuteAction::CreateRaw(this, &FExtendMenuBase::NewMainMenuEntryAction))
	);

	MenuBuilder.EndSection();	                                       // 结束Section设置
}

void FExtendMenuBase::NewMainMenuEntryAction()
{
	UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:NewMainMenuEntryAction Clicked"),__FUNCTIONW__,__LINE__);
	
	// 开始构造 SCustomDialog
	TSharedRef<SCustomDialog> HelloWorldDialog = SNew(SCustomDialog)
		.Title(FText(LOCTEXT("HelloWorldTitleExample", "Hello, World!")))
		.DialogContent( // 添加 DialogContent，类型为 SWidget
			SNew(STextBlock).Text(FText::FromString("This is a Custom Dialog.")))
		.IconBrush("Icons.Download")  // 只可使用 CoreStyle 中已注册的 Icon
		.Buttons({
			SCustomDialog::FButton(LOCTEXT("OK", "OK")),
			SCustomDialog::FButton(LOCTEXT("Cancel", "Cancel"))
		});

	// 显示 SCustomDialog
	HelloWorldDialog->ShowModal();
}

void FExtendMenuBase::ExtendContentBrowserByFExtend()
{
	// 新的FContentBrowserModule模块
	FContentBrowserModule& ContentBrowserModule = 
	FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>("ContentBrowser");

	// 通过GetAllAssetContextMenuExtenders获取Extenders
	TArray<FContentBrowserMenuExtender_SelectedPaths>& Extenders = 
	ContentBrowserModule.GetAllAssetContextMenuExtenders();
	
	// 注意此处添加代理应与Extenders中对应
	Extenders.Add(FContentBrowserMenuExtender_SelectedPaths::CreateRaw(
	this, &FExtendMenuBase::ExtendAssetContextMenu));
	
	// 通过AssetViewContextMenuExtenders拓展选定资产上下文菜单
	TArray<FContentBrowserMenuExtender_SelectedAssets>& Extenders2 = 
	ContentBrowserModule.GetAllAssetViewContextMenuExtenders();

	Extenders2.Add(FContentBrowserMenuExtender_SelectedAssets::CreateRaw(
	this, &FExtendMenuBase::ExtendAssetViewContextMenu));
}

TSharedRef<FExtender> FExtendMenuBase::ExtendAssetContextMenu(const TArray<FString>& SelectedPaths)
{
	TSharedRef<FExtender> MenuExtender(new FExtender());

	if(SelectedPaths.Num() > 0)
	{
		MenuExtender->AddMenuExtension(
			// "ContentBrowserGetContent",
		"ContentBrowserNewFolder",
			EExtensionHook::Before,
			nullptr,
			FMenuExtensionDelegate::CreateRaw(this, &FExtendMenuBase::MakeAssetContextMenuEntry));
	}
	return MenuExtender;
}

void FExtendMenuBase::MakeAssetContextMenuEntry(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(
		FText::FromString("Asset Context Menu Button"),
		FText::FromString("This is a asset context menu button"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &FExtendMenuBase::AssetContextMenuEntryAction))
		);
}

void FExtendMenuBase::AssetContextMenuEntryAction()
{
	UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:AssetContextMenuEntryAction Clicked"),__FUNCTIONW__,__LINE__);
}


TSharedRef<FExtender> FExtendMenuBase::ExtendAssetViewContextMenu(const TArray<FAssetData>& SelectedAssets)
{
	TSharedRef<FExtender> MenuExtender(new FExtender());
	
	if(SelectedAssets.Num() > 0)
	{
		MenuExtender->AddMenuExtension(
			"GetAssetActions",
			EExtensionHook::Before,
			nullptr,
			FMenuExtensionDelegate::CreateRaw(
			this, &FExtendMenuBase::MakeAssetViewContextMenuEntry));
	}

	return MenuExtender;
}

void FExtendMenuBase::MakeAssetViewContextMenuEntry(FMenuBuilder& MenuBuilder)
{
	// 尝试添加Section
	MenuBuilder.BeginSection("Section 1", FText::FromString("Section 1"));

	MenuBuilder.AddMenuEntry(
		FText::FromString("Asset View Context Menu Button"),
		FText::FromString("This is a asset view context menu button"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &FExtendMenuBase::AssetViewContextMenuEntryAction))
		);

	MenuBuilder.EndSection();
}

void FExtendMenuBase::AssetViewContextMenuEntryAction()
{
	UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:AssetViewContextMenuEntryAction Clicked"),__FUNCTIONW__,__LINE__);
}

void FExtendMenuBase::ExtendViewportByFExtend()
{
	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));

	// GetAllLevelViewportContextMenuExtenders
	TArray<FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors>& LevelViewportContextMenuExtenders =
		LevelEditorModule.GetAllLevelViewportContextMenuExtenders();

	LevelViewportContextMenuExtenders.Add(FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors::CreateRaw(
		this, &FExtendMenuBase::ExtendViewportSelectedActorMenu));
}

TSharedRef<FExtender> FExtendMenuBase::ExtendViewportSelectedActorMenu(const TSharedRef<FUICommandList> UICommandList, const TArray<AActor*> SelectedActors)
{
	TSharedRef<FExtender> MenuExtender(new FExtender());

	if(SelectedActors.Num() > 0)
	{
		MenuExtender->AddMenuExtension(
			// "ActorOptions",
		"ActorAsset",
			EExtensionHook::Before,
			nullptr,
			FMenuExtensionDelegate::CreateRaw(this, &FExtendMenuBase::MakeViewportActorMenuEntry));
	}
	return MenuExtender;
}

void FExtendMenuBase::MakeViewportActorMenuEntry(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(
		FText::FromString("Viewport Actor Menu Button"),
		FText::FromString("This is a viewport actor menu button"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &FExtendMenuBase::ViewportActorMenuEntryAction)));
}

void FExtendMenuBase::ViewportActorMenuEntryAction()
{
	UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:ViewportActorMenuEntryAction Clicked"),__FUNCTIONW__,__LINE__);
}

/*************************************** UToolMenus *************************************/

void FExtendMenuBase::ExtendByUToolMenus()
{
	// 持有LevelEditor.MainMenu
	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu");

	// 定位LevelEditor.MainMenu中的Section
	// LevelEditor.MainMenu没有Section因此传入NAME_None
	FToolMenuSection& Section = Menu->FindOrAddSection(NAME_None);

	// 开始制作子菜单Entry
	FToolMenuEntry& MakeEntry =
		Section.AddSubMenu(
			"NewMenuByUToolMenus",                  // 新子菜单 Name
			LOCTEXT("NewMenu2", "New Menu 2"),      // 标签
			LOCTEXT("NewMenu2_ToolTip", "This is a extended menu by UToolMenus"), // ToolTip
			FNewToolMenuChoice()                    // 在这里还可以做一些奇怪的事情
			);
	// 设置Entry出现的位置
	MakeEntry.InsertPosition = FToolMenuInsert("Help", EToolMenuInsertType::After);

	// LevelEditor.MainMenu.NewMenuByUToolMenus注册为新菜单
	static const FName BaseMenuName = "LevelEditor.MainMenu.NewMenuByUToolMenus";
	Menu = UToolMenus::Get()->RegisterMenu(BaseMenuName);

	// 在新菜单下添加Section和Entry
	FToolMenuSection& NewSection = Menu->AddSection("New Section", FText::FromString("New Section"));
	NewSection.AddMenuEntry(
		"New Menu 2 Button",
		FText::FromString("Label: New Menu 2 Button"),
		FText::FromString("This is a new menu 2 button by UToolMenus"),
		FSlateIcon(),
		FToolUIActionChoice(FExecuteAction::CreateRaw(this, &FExtendMenuBase::NewMenu2ButtonAction))
		);
}

void FExtendMenuBase::NewMenu2ButtonAction()
{
	UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:NewMenu2ButtonAction Clicked"),__FUNCTIONW__,__LINE__);

	++ClickCount;
	FString str = TEXT("呀~ 被戳了 ") + FString::FromInt(ClickCount) + TEXT(" 下！~~❤");
	FText Message = FText::FromString(str);

	// 构造 FNotificationInfo
	FNotificationInfo NotifyInfo(Message);
	// 使用大字体
	NotifyInfo.bUseLargeFont = true;
	// 设定通知显示时长
	NotifyInfo.FadeOutDuration = 7.f;
	// 设定通知 Icon
	NotifyInfo.Image = FExtendEditorStyle::GetStyleSet()->GetBrush("AliceTool");

	// 利用 FNotificationInfo 发送通知
	FSlateNotificationManager::Get().AddNotification(NotifyInfo);
}


/*************************************** bind to LevelEditor module's delegate *************************************/
void FExtendMenuBase::OnLevelEditorCreatedEvent(TSharedPtr<ILevelEditor> Editor)
{
	ExtendByUToolMenus();
}


/*************************************** style set *************************************/

void FExtendMenuBase::StyleSample()
{
	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");

	FToolMenuSection& Section = Menu->FindOrAddSection(FName("Settings"));
	Section.AddEntry(FToolMenuEntry::InitToolBarButton(  // 添加一个ToolBar按钮
		"Style Button",
		FToolUIActionChoice(FExecuteAction::CreateRaw(this, &FExtendMenuBase::StyleButtonAction)),
		FText::FromString("Label: Style Buttom"),
		FText::FromString("This is a style button by Style Sample"),
		FSlateIcon(                                  // 使用自己注册的FSlateStyleSet设置Icon样式
		FExtendEditorStyle::GetStyleSetName(), "AliceTool"))
		);
}

void FExtendMenuBase::StyleButtonAction()
{
	UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:StyleButtonAction Clicked"),__FUNCTIONW__,__LINE__);
	
	if(!MessageDelegate)
	{
		MessageDelegate = NewObject<UMessageClass>();
		MessageDelegate->AddToRoot();
		MessageDelegate->SetMessage(
		FText::FromString("This is a Binded Message."), FLinearColor::White);

		if(!MessageDelegate->IsBind())
		{
			MessageDelegate->BindToViewportStatsSubsystem();
		}
	}

	MessageDelegate->ToggleDisplay();
}

/*************************************** CommandUI *************************************/
void FExtendMenuBase::CommandSample()
{
	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
	FToolMenuSection& Section = Menu->FindOrAddSection(FName("Settings"));

	// 使用 Command 方式生成 ToolBarEntry
	FToolMenuEntry ToolMenuEntry = FToolMenuEntry::InitToolBarButton(FExtendEditorCommands::Get().PrintLog);
	// 为 ToolBarEntry 配置CommandList
	ToolMenuEntry.SetCommandList(FExtendEditorCommands::Get().CommandList);
	// 将配置好的 ToolBarEntry 添加到指定位置
	Section.AddEntry(ToolMenuEntry);
}

#undef LOCTEXT_NAMESPACE 
