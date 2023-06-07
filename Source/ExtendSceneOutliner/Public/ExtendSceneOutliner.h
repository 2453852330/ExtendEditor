#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FExtendSceneOutlinerModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    // 注册 OutLiner
    void InitSceneOutlinerColumn();
    void UninitSceneOutlinerColumn();

    TSharedRef<class ISceneOutlinerColumn> OnCreateSceneOutlinerLockColumnInfo(class ISceneOutliner& SceneOutliner);


    
private:
    // 锁定
    void InitCustomSelectionEvent();
    void UninitCustomSelectionEvent();
    void OnActorSelected(UObject* SelectedObject);
    bool GetEditorActorSubsystem();

public:

    bool CheckIsActorSelectionLocked(AActor* SelectedActor);
    void LockActorSelection(AActor* ActorToProcess);
    void UnlockActorSelection(AActor* ActorToProcess);
    void SetActorSelectionState(AActor* Actor, bool bShouldBeSelected);

private:
    // UE5
    // TWeakObjectPtr<class UEditorActorSubsystem> WeakEditorActorSubsystem;
    
    FDelegateHandle SelectObjectEventHandle;
};
