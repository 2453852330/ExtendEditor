#include "CustomSlate/CustomSlate.h"

#include "Editor.h"
#include "EditorUtilitySubsystem.h"
#include "EditorUtilityWidgetBlueprint.h"
#include "FExtendEditorStyle.h"
#include "ToolMenus.h"
#include "Modules/ModuleManager.h"
#include "Widgets/Layout/SConstraintCanvas.h"

IMPLEMENT_MODULE(FCustomSlateModule, CustomSlate)

#define LOCTEXT_NAMESPACE "CustomSlateNS"

void FCustomSlateModule::StartupModule()
{
	CreateButtonByStyle();
	RegisterTab();
}

void FCustomSlateModule::ShutdownModule()
{
	// 在模块注销时注销
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(FName("AliceTab"));
	
	// 在模块注销时注销
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(FName("MainLayoutTab"));
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(FName("SubTab.1"));
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(FName("SubTab.2"));
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(FName("SubTab.3"));
}

void FCustomSlateModule::CreateButtonByStyle()
{
	UToolMenu * Menu = UToolMenus::Get()->ExtendMenu(TEXT("LevelEditor.LevelEditorToolBar"));
	FToolMenuSection & Section = Menu->FindOrAddSection(TEXT("Settings"));

	Section.AddEntry(FToolMenuEntry::InitToolBarButton(
		TEXT("CustomSlate"),
		FToolUIActionChoice(FExecuteAction::CreateRaw(this,&FCustomSlateModule::ButtonAction)),
		LOCTEXT("ASHIOAJ","CustomSlate"),
		LOCTEXT("ASIOFJAOFI","This is a button to Test Custom Slate"),
		FSlateIcon(FExtendEditorStyle::GetStyleSetName(),FName("CustomSlate"))
	));
}

/*************************************** Button Clicked Event *************************************/
void FCustomSlateModule::ButtonAction()
{
	// RunEditorUtilityWidget();
	// SpawnWindow();
	// SpawnTab();
	SpawnLayoutTab();
}

void FCustomSlateModule::RunEditorUtilityWidget()
{
	// EditorUtilityWidgetBlueprint'/Game/NewEditorUtilityWidgetBlueprint.NewEditorUtilityWidgetBlueprint'
	UObject * Blueprint = LoadObject<UObject>(nullptr,TEXT("/Game/NewEditorUtilityWidgetBlueprint"));
	UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:Load Editor Widget Result : %s"),__FUNCTIONW__,__LINE__,Blueprint?TEXT("Success"):TEXT("Failed"));
	if (Blueprint)
	{
		UEditorUtilityWidgetBlueprint * EditorWidget = Cast<UEditorUtilityWidgetBlueprint>(Blueprint);
		if (EditorWidget)
		{
			UEditorUtilitySubsystem * EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
			EditorUtilitySubsystem->SpawnAndRegisterTab(EditorWidget);
		}
	}
}

/*************************************** Spawn Window *************************************/
void FCustomSlateModule::SpawnWindow()
{
	// 创建新窗口
	TSharedRef<SWindow> Window = SNew(SWindow)
	.Title(FText::FromString("Alice Window"))
	.SizingRule(ESizingRule::UserSized)
	.ClientSize(FVector2D(1000.f, 700.f))
	.AutoCenter(EAutoCenter::PreferredWorkArea)
	.ScreenPosition(FVector2D(0, 0))
	.IsEnabled(true)
	.SupportsMinimize(true)
	.SupportsMaximize(true);
	
	// 设置窗口内容
	Window->SetContent
	(
		SNew(SConstraintCanvas)
		+SConstraintCanvas::Slot()
		.Alignment(0.5f)
		.Anchors(0.5f)
		.Offset(FMargin(0.0f, 0.0f, 300.f, 100.f))
		.AutoSize(true)
		[
			SNew(STextBlock)
			.Text(FText::FromString("Hello, Alice Window !"))
		]
	);

	// 显示新窗口
	FSlateApplication::Get().AddWindow(Window);
}

/*************************************** Spawn Tab *************************************/

void FCustomSlateModule::RegisterTab()
{
	// 注册新 Tab
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(FName("AliceTab"),
		FOnSpawnTab::CreateRaw(this, &FCustomSlateModule::OnSpawnTab))
	.SetDisplayName(FText::FromString(TEXT("Alice Tab")));
}

void FCustomSlateModule::SpawnTab()
{
	// 显示新 Tab，注册后可以在任意地方这样做
	FGlobalTabmanager::Get()->TryInvokeTab(FName("AliceTab"));
}

TSharedRef<SDockTab> FCustomSlateModule::OnSpawnTab(const FSpawnTabArgs& Args)
{
	TSharedRef<SDockTab> Tab = SNew(SDockTab).TabRole(ETabRole::NomadTab);
	
	Tab->SetContent
	(
		SNew(SConstraintCanvas)
		+SConstraintCanvas::Slot()
		.Alignment(0.5f)
		.Anchors(0.5f)
		.Offset(FMargin(0.0f, 0.0f, 300.f, 100.f))
		.AutoSize(true)
		[
			SNew(STextBlock)
			.Text(FText::FromString("Hello, Alice Tab !"))
		]
	);
	
	return Tab;
}

/*************************************** LayoutTab *************************************/

void FCustomSlateModule::SpawnLayoutTab()
{
	// 注册 Tab
	// FOnSpawnMainTab
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(FName("MainLayoutTab"),
		FOnSpawnTab::CreateRaw(this, &FCustomSlateModule::FOnSpawnMainTab))
	.SetDisplayName(FText::FromString("Layout Tab"));

	// FOnSpawnSubTab
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(FName("SubTab.1"),
		FOnSpawnTab::CreateRaw(this, &FCustomSlateModule::FOnSpawnSubTab,
			FText::FromString("This is Sub-Tab 1.")))
	.SetDisplayName(FText::FromString("SubTab 1"));

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(FName("SubTab.2"),
		FOnSpawnTab::CreateRaw(this, &FCustomSlateModule::FOnSpawnSubTab, 
			FText::FromString("This is Sub-Tab 2.")))
	.SetDisplayName(FText::FromString("SubTab 2"));

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(FName("SubTab.3"),
		FOnSpawnTab::CreateRaw(this, &FCustomSlateModule::FOnSpawnSubTab, 
			FText::FromString("This is Sub-Tab 3.")))
	.SetDisplayName(FText::FromString("SubTab 3"));

	// 查找已有Tab 防止反复生成Tab
	TSharedPtr<SDockTab> ExistingTab = 
		FGlobalTabmanager::Get()->FindExistingLiveTab(FName("MainLayoutTab"));
	
	if(!ExistingTab.IsValid())
	{
		// 如果没有已存在的Tab，生成Tab
		FGlobalTabmanager::Get()->TryInvokeTab(FName("MainLayoutTab"));
	}
	else
	{
		// 如果Tab已存在，关闭Tab
		ExistingTab->RequestCloseTab();
	}
}

TSharedRef<SDockTab> FCustomSlateModule::FOnSpawnMainTab(const FSpawnTabArgs& Args)
{
	TSharedRef<SDockTab> MainTab = SNew(SDockTab).TabRole(ETabRole::NomadTab);

	if(!TabManager.IsValid())
	{
		// 新建一个专用的TabManager，我们将用这个TabManager来恢复布局
		TabManager = FGlobalTabmanager::Get()->NewTabManager(MainTab);
	}

	if(!TabManagerLayout.IsValid())
	{
		// 生成布局
		TabManagerLayout = FTabManager::NewLayout("AliceTabManagerLayout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(.4f)
					->AddTab("SubTab.1", ETabState::OpenedTab)
					->SetHideTabWell(true)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(.4f)
					->AddTab("SubTab.2", ETabState::OpenedTab)
					->SetHideTabWell(true)
				)
			)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(.4f)
				->AddTab("SubTab.3", ETabState::OpenedTab)
				->SetHideTabWell(true)
			)
		);
	}

	// 恢复布局
	TSharedRef<SWidget> TabContents = TabManager->RestoreFrom(
		TabManagerLayout.ToSharedRef(), TSharedPtr<SWindow>()).ToSharedRef();

	MainTab->SetContent
	(
		TabContents
	);

	return MainTab;
}

TSharedRef<SDockTab> FCustomSlateModule::FOnSpawnSubTab(const FSpawnTabArgs& Args, FText Text)
{
	TSharedRef<SDockTab> Tab = SNew(SDockTab).TabRole(ETabRole::NomadTab);

	Tab->SetContent
	(
		SNew(SConstraintCanvas)
		+SConstraintCanvas::Slot()
		.Alignment(0.5f)
		.Anchors(0.5f)
		.Offset(FMargin(0.0f, 0.0f, 300.f, 100.f))
		.AutoSize(true)
		[
			SNew(STextBlock)
			.Text(Text)
		]
	);

	return Tab;
}


#undef LOCTEXT_NAMESPACE
