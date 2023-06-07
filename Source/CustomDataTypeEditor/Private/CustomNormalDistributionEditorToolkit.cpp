#include "CustomNormalDistributionEditorToolkit.h"
#include "Widgets/Docking/SDockTab.h"
#include "SCustomNormalDistributionWidget.h"
#include "Modules/ModuleManager.h"

// 资产双击,打开资产编辑器
// 注册了 TagLayout,使用了 Tab
void FCustomNormalDistributionEditorToolkit::InitEditor(const TArray<UObject*>& InObjects)
{
	// 获取自定义类型
	NormalDistribution = Cast<UCustomNormalDistribution>(InObjects[0]);

	// 创建 TabLayout
	const TSharedRef<FTabManager::FLayout> Layout = 
		FTabManager::NewLayout("CustomNormalDistributionEditorLayout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewSplitter()
				->SetSizeCoefficient(0.6f)
				->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.8f)
					// 添加 CustomNormalDistributionPDFTab
					->AddTab("CustomNormalDistributionPDFTab", ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.2f)
					// 添加 CustomNormalDistributionDetailsTab
					->AddTab("CustomNormalDistributionDetailsTab", ETabState::OpenedTab)
				)
			)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.4f)
				->AddTab("OutputLog", ETabState::OpenedTab)
			)
		);
	// 使用自定义的Layout
	FAssetEditorToolkit::InitAssetEditor(EToolkitMode::Standalone, {},
		"CustomNormalDistributionEditor", Layout,
		true, true, InObjects);
}

// 注册 Tab
void FCustomNormalDistributionEditorToolkit::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	// 初始化 WorkSpace
	WorkspaceMenuCategory = 
		InTabManager->AddLocalWorkspaceMenuCategory(INVTEXT("CustomNormalDistributionTabs"));

	// 注册 SCustomNormalDistributionWidget TabSpawner
	InTabManager->RegisterTabSpawner("CustomNormalDistributionPDFTab", 
		FOnSpawnTab::CreateLambda([=](const FSpawnTabArgs&)
		{
			return SNew(SDockTab)
			[
				SNew(SCustomNormalDistributionWidget)
				.Mean(this, &FCustomNormalDistributionEditorToolkit::GetMean)
				.StandardDeviation(this, &FCustomNormalDistributionEditorToolkit::GetStandardDeviation)
				.OnMeanChanged(this, &FCustomNormalDistributionEditorToolkit::SetMean)
				.OnStandardDeviationChanged(this, &FCustomNormalDistributionEditorToolkit::SetStandardDeviation)
			];
		}))
	.SetDisplayName(INVTEXT("PDF"))
	.SetGroup(WorkspaceMenuCategory.ToSharedRef());

	// 创建 CustomNormalDistribution DetailsView
	FPropertyEditorModule& PropertyEditorModule = 
		FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	TSharedRef<IDetailsView> DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObjects(TArray<UObject*>{ NormalDistribution });

	// 注册 CustomNormalDistribution DetailsView TabSpawner
	InTabManager->RegisterTabSpawner("CustomNormalDistributionDetailsTab", 
		FOnSpawnTab::CreateLambda([=](const FSpawnTabArgs&)
		{
			return SNew(SDockTab)
			[
				DetailsView
			];
		}))
	.SetDisplayName(INVTEXT("Details"))
	.SetGroup(WorkspaceMenuCategory.ToSharedRef());
}

void FCustomNormalDistributionEditorToolkit::UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
	InTabManager->UnregisterTabSpawner("CustomNormalDistributionPDFTab");
	InTabManager->UnregisterTabSpawner("CustomNormalDistributionDetailsTab");
}

float FCustomNormalDistributionEditorToolkit::GetMean() const
{
	return NormalDistribution->Mean;
}

float FCustomNormalDistributionEditorToolkit::GetStandardDeviation() const
{
	return NormalDistribution->StandardDeviation;
}

void FCustomNormalDistributionEditorToolkit::SetMean(float Mean)
{
	// 因为在Slate中启用了Transaction
	NormalDistribution->Modify();
	NormalDistribution->Mean = Mean;
}

void FCustomNormalDistributionEditorToolkit::SetStandardDeviation(float StandardDeviation)
{
	NormalDistribution->Modify();
	NormalDistribution->StandardDeviation = StandardDeviation;
}