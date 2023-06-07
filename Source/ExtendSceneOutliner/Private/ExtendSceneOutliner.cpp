#include "ExtendSceneOutliner.h"

#include "ExtendSceneOutlinerStyle.h"
#include "SceneOutlinerLockColumn.h"
#include "SceneOutlinerModule.h"
#include "Engine/Selection.h"

#define LOCTEXT_NAMESPACE "FExtendSceneOutlinerModule"

void FExtendSceneOutlinerModule::StartupModule()
{
    // Create StyleSet
    FExtendSceneOutlinerStyle::Initialize();
    InitSceneOutlinerColumn();

    // 注册Actor选中Delegate
    InitCustomSelectionEvent();
}

void FExtendSceneOutlinerModule::ShutdownModule()
{
    FExtendSceneOutlinerStyle::UnInitialize();
    UninitSceneOutlinerColumn();
    // 取消注册Actor选中Delegate
    UninitSceneOutlinerColumn();
}

// 注册
void FExtendSceneOutlinerModule::InitSceneOutlinerColumn()
{
    // FSceneOutlinerColumnInfo SceneOutlinerLockColumnInfo(
    //     ESceneOutlinerColumnVisibility::Visible,  // 可见性
    //     1,					  // Column 出现的位置
    //     FCreateSceneOutlinerColumn::CreateRaw(
    //         this, 
    //         &FExtendSceneOutliner::OnCreateSceneOutlinerLockColumnInfo)
    //     );

    // 创建 SceneOutliner::FDefaultColumnInfo 对象
    SceneOutliner::FDefaultColumnInfo SceneOutlinerLockColumnInfo
     = SceneOutliner::FDefaultColumnInfo(SceneOutliner::FColumnInfo(
            SceneOutliner::EColumnVisibility::Visible,
            1,
            FCreateSceneOutlinerColumn::CreateRaw(
                this,
                 &FExtendSceneOutlinerModule::OnCreateSceneOutlinerLockColumnInfo)
     ));
    // 获取 SceneOutliner 模块
    FSceneOutlinerModule& SceneOutlinerModule = 
        FModuleManager::LoadModuleChecked<FSceneOutlinerModule>(TEXT("SceneOutliner"));
	// 使用自定义类FSceneOutlinerLockColumn进行注册
    SceneOutlinerModule.RegisterDefaultColumnType<FSceneOutlinerLockColumn>(SceneOutlinerLockColumnInfo);
}

void FExtendSceneOutlinerModule::UninitSceneOutlinerColumn()
{
    FSceneOutlinerModule& SceneOutlinerModule = 
        FModuleManager::LoadModuleChecked<FSceneOutlinerModule>(TEXT("SceneOutliner"));
    SceneOutlinerModule.UnRegisterColumnType<FSceneOutlinerLockColumn>();
}

TSharedRef<ISceneOutlinerColumn> FExtendSceneOutlinerModule::OnCreateSceneOutlinerLockColumnInfo(ISceneOutliner& SceneOutliner)
{
    // 直接使用自定义类进行创建;
    return MakeShareable(new FSceneOutlinerLockColumn(SceneOutliner));
}

// 锁定

void FExtendSceneOutlinerModule::InitCustomSelectionEvent()
{
    USelection* UserSelection = GEditor->GetSelectedActors();
    SelectObjectEventHandle = 
        UserSelection->SelectObjectEvent.AddRaw(this, &FExtendSceneOutlinerModule::OnActorSelected);
}

void FExtendSceneOutlinerModule::UninitCustomSelectionEvent()
{
    USelection* UserSelection = GEditor->GetSelectedActors();
    UserSelection->SelectObjectEvent.Remove(SelectObjectEventHandle);
}

void FExtendSceneOutlinerModule::OnActorSelected(UObject* SelectedObject)
{
    // always true
    if(!GetEditorActorSubsystem()) return;
	
    if(AActor* SelectedActor = Cast<AActor>(SelectedObject))
    {
        // 检测是否有 Lock Tag
        if(CheckIsActorSelectionLocked(SelectedActor))
        {
            // WeakEditorActorSubsystem.Get()->SetActorSelectionState(SelectedActor, false);
            // 检测到Actor已经被锁定了,就取消选中
            GEditor->SelectActor(SelectedActor,false,true);
        }
    }
}

bool FExtendSceneOutlinerModule::GetEditorActorSubsystem()
{
    // if(!WeakEditorActorSubsystem.IsValid())
    // {
    //     WeakEditorActorSubsystem = GEditor->GetEditorSubsystem<UEditorActorSubsystem>();
    // }
    // return WeakEditorActorSubsystem.IsValid();
    return true;
}

// 通过Tag检测,Actor是否已经选中
bool FExtendSceneOutlinerModule::CheckIsActorSelectionLocked(AActor* SelectedActor)
{
    if(!SelectedActor) return false;
    return SelectedActor->ActorHasTag(FName("Locked"));
}

void FExtendSceneOutlinerModule::LockActorSelection(AActor* ActorToProcess)
{
    if(!ActorToProcess) return;
    if(!ActorToProcess->ActorHasTag(FName("Locked")))
    {
        ActorToProcess->Tags.Add(FName("Locked"));
    }
}

void FExtendSceneOutlinerModule::UnlockActorSelection(AActor* ActorToProcess)
{
    if(!ActorToProcess) return;
    if(ActorToProcess->ActorHasTag(FName("Locked")))
    {
        ActorToProcess->Tags.Remove(FName("Locked"));
    }
}

void FExtendSceneOutlinerModule::SetActorSelectionState(AActor* Actor, bool bShouldBeSelected)
{
    if (!Actor)
    {
        return;
    }
    // WeakEditorActorSubsystem->SetActorSelectionState(Actor, bShouldBeSelected);
    GEditor->SelectActor(Actor,bShouldBeSelected,true);    
}


#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FExtendSceneOutlinerModule, ExtendSceneOutliner)