#include "SceneOutlinerLockColumn.h"

#include "ActorTreeItem.h"
#include "ComponentTreeItem.h"
#include "Editor.h"
#include "ExtendSceneOutliner.h"
#include "ExtendSceneOutlinerStyle.h"
#include "ISceneOutliner.h"
#include "LevelEditor.h"
#include "SubComponentTreeItem.h"
#include "WorldTreeItem.h"
#include "Engine/Selection.h"
#include "Widgets/Images/SImage.h"


struct MyTreeItemVisitor : SceneOutliner::IMutableTreeItemVisitor
{
	mutable TWeakObjectPtr<AActor> _Actor;
	mutable TWeakObjectPtr<UWorld> _World;
	mutable TWeakObjectPtr<UActorComponent> _ActorComponent;
	mutable bool _bIsFolder = false;
	mutable bool _bIsSubComponent = false;
	
	virtual void Visit(SceneOutliner::FActorTreeItem& Actor) const override
	{
		_Actor = Actor.Actor;
	};
	virtual void Visit(SceneOutliner::FWorldTreeItem& World) const override
	{
		_World = World.World;
	};
	virtual void Visit(SceneOutliner::FFolderTreeItem& Folder) const override
	{
		_bIsFolder = true;
	};
	virtual void Visit(SceneOutliner::FComponentTreeItem& Folder) const override
	{
		_ActorComponent = Folder.Component;
	};
	virtual void Visit(SceneOutliner::FSubComponentTreeItem& Folder) const override
	{
		_bIsSubComponent = true;
	};
};

// 在标题头添加 SImage
SHeaderRow::FColumn::FArguments FSceneOutlinerLockColumn::ConstructHeaderRowColumn()
{
	SHeaderRow::FColumn::FArguments ConstructedHeaderRowColumn =
		SHeaderRow::Column(GetColumnID())
		.FixedWidth(24.f)
		.HAlignHeader(HAlign_Center)
		.VAlignHeader(VAlign_Center)
		.HAlignCell(HAlign_Center)
		.VAlignCell(VAlign_Center)
		.DefaultTooltip(FText::FromString(TEXT("Lock the transformation of actor")))
		[
			SNew(SImage)
			.ColorAndOpacity(FSlateColor::UseForeground())
			.Image(FExtendSceneOutlinerStyle::GetStyleSet().Get()->GetBrush("SceneOutliner.Lock"))
		];

	return ConstructedHeaderRowColumn;
}

// 在标题行添加 NullWidget
const TSharedRef<SWidget> FSceneOutlinerLockColumn::ConstructRowWidget(
	SceneOutliner::FTreeItemRef TreeItem,
	const STableRow<SceneOutliner::FTreeItemPtr>& Row)
{
	{
		// 暂时返回一个空 Widget
		// return SNullWidget::NullWidget;
	}
	
	{
		
		// Cast不支持Struct
		// SceneOutliner::FActorTreeItem* ActorTreeItem =Cast<SceneOutliner::FActorTreeItem,SceneOutliner::ITreeItem>(&TreeItem.Get()) ;
		// dynamic_cast 会检测结果,要在Build.cs中开启 bUseRTTI = true,依然会崩溃,
		// 所以,直接强制转换,当场景出现非Actor对象,比如Folder时会崩溃;
		MyTreeItemVisitor MyTreeItemVisitor;
		TreeItem->Visit(MyTreeItemVisitor);
		
		// 其他情况返回NullWidget
		if (MyTreeItemVisitor._bIsFolder || MyTreeItemVisitor._bIsSubComponent || MyTreeItemVisitor._ActorComponent.IsValid() || MyTreeItemVisitor._World.IsValid())
		{
			return SNullWidget::NullWidget;
		}
		// 只处理 Actor
		SceneOutliner::FActorTreeItem* ActorTreeItem = (SceneOutliner::FActorTreeItem*)(&TreeItem.Get());
		
		// 检查是否转换成功
		// if(!ActorTreeItem || !ActorTreeItem->IsValid()) return SNullWidget::NullWidget;
		if (!ActorTreeItem)
		{
			return SNullWidget::NullWidget;
		}

		// 测试2新增,检测是否已经锁定移动
		// 检测 Actor 锁定移动的状态
		// const bool bIsActorLocked = ActorTreeItem->Actor->IsLockLocation(); // UE5
		// const bool bIsActorLocked = ActorTreeItem->Actor->bLockLocation; // UE4

		// 测试4
		FExtendSceneOutlinerModule& ExtendSceneOutlinerModule = 
		FModuleManager::LoadModuleChecked<FExtendSceneOutlinerModule>(TEXT("ExtendSceneOutliner"));
		const bool bIsActorLocked = ExtendSceneOutlinerModule.CheckIsActorSelectionLocked(ActorTreeItem->Actor.Get());
		
		// 获取 SlateStyle
		const FCheckBoxStyle& ToggleButtonStyle = FExtendSceneOutlinerStyle::GetStyleSet()->GetWidgetStyle<FCheckBoxStyle>(
			   FName("SceneOutliner.LockToggle"));
		
		// 创建 SCheckBox Widget
		TSharedRef<SWidget> ConstructedRowWidget =
			SNew(SCheckBox)
			 .Visibility(EVisibility::Visible)
			 .Type(ESlateCheckBoxType::ToggleButton)
			 .Style(&ToggleButtonStyle)
			 .HAlign(HAlign_Center)
			 // .IsChecked(ECheckBoxState::Unchecked) // 01
			 .IsChecked(bIsActorLocked?ECheckBoxState::Checked:ECheckBoxState::Unchecked) // 02
			 .OnCheckStateChanged(
				this,
				// 状态改变绑定
				&FSceneOutlinerLockColumn::OnLockToggleStateChanged_LockSelection_SelectedActors,ActorTreeItem->Actor);
	
		return ConstructedRowWidget;
	}
}

void FSceneOutlinerLockColumn::OnLockToggleStateChanged(ECheckBoxState NewState, TWeakObjectPtr<AActor> Actor)
{
	if(NewState == ECheckBoxState::Checked)
	{
		FString ActorName = Actor.Get()->GetActorLabel();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Locked ") + ActorName);
		return;
	}

	if(NewState == ECheckBoxState::Unchecked)
	{
		FString ActorName = Actor.Get()->GetActorLabel();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Unlock ") + ActorName);
		return;
	}

	return;
}

void FSceneOutlinerLockColumn::OnLockToggleStateChanged_LockMovement_SelectedActor(ECheckBoxState NewState, TWeakObjectPtr<AActor> Actor)
{
	// UEditorActorSubsystem* EditorActorSubsystem = GEditor->GetEditorSubsystem<UEditorActorSubsystem>();

	if(NewState == ECheckBoxState::Checked)
	{
		// 锁定 Actor 移动
		// Actor->SetLockLocation(true);
		
		Actor->bLockLocation = true;

		// 刷新 Actor 选择状态
		// EditorActorSubsystem->SetActorSelectionState(Actor.Get(), false);
		// EditorActorSubsystem->SetActorSelectionState(Actor.Get(), true);
 		
		return;
	}

	if(NewState == ECheckBoxState::Unchecked)
	{
		// 解锁 Actor 移动
		// Actor->SetLockLocation(false);

		Actor->bLockLocation = false;
		
		// 刷新 Actor 选择状态
		// EditorActorSubsystem->SetActorSelectionState(Actor.Get(), false);
		// EditorActorSubsystem->SetActorSelectionState(Actor.Get(), true);

		return;
	}
	
	return;
}

void FSceneOutlinerLockColumn::OnLockToggleStateChanged_LockMovement_SelectedActors(ECheckBoxState NewState, TWeakObjectPtr<AActor> Actor)
{
	FLevelEditorModule& LevelEditorModule = 
		FModuleManager::LoadModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));

	TSharedPtr<ISceneOutliner> SceneOutliner = 
		LevelEditorModule.GetFirstLevelEditor()->GetSceneOutliner();

	// UE5
	// UEditorActorSubsystem* EditorActorSubsystem = GEditor->GetEditorSubsystem<UEditorActorSubsystem>();

	// 获取 ActorSelection
	USelection* SelectedActors = GEditor->GetSelectedActors();
	UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:Selected %d Actors"),__FUNCTIONW__,__LINE__,SelectedActors->Num());
	
	// SelectedActors->Num() == 0 当选择最顶层的Map时,Num=0;
	
	if(NewState == ECheckBoxState::Checked)
	{
		// 如果没有选中任何 Actor，仅发生了按钮的点击事件
		if(SelectedActors->Num() == 0)
		{
			Actor->bLockLocation = true;
			
			// UE5
			// Actor->SetLockLocation(true);
			// EditorActorSubsystem->SetActorSelectionState(Actor.Get(), false);
			// EditorActorSubsystem->SetActorSelectionState(Actor.Get(), true);
		}
		else
		{
			for(FSelectionIterator It(*SelectedActors); It; ++It)
			{
				AActor* SelectedActor = Cast<AActor>( *It );

				// SelectedActor->SetLockLocation(true);
				if (SelectedActor)
				{
					SelectedActor->bLockLocation = true;
				}
			}

			// for(FSelectionIterator It(*SelectedActors); It; ++It)
			// {
			// 	AActor* SelectedActor = Cast<AActor>( *It );
			//
			// 	EditorActorSubsystem->SetActorSelectionState(SelectedActor, false);
			// 	EditorActorSubsystem->SetActorSelectionState(SelectedActor, true);
			// }
		}
		
		// 设置完毕后刷新 SceneOutliner 重新生成图标
		if(SceneOutliner.IsValid())
		{
			SceneOutliner->FullRefresh();
		}
 		
		return;
	}

	if(NewState == ECheckBoxState::Unchecked)
	{
		if(SelectedActors->Num() == 0)
		{
			Actor->bLockLocation = false;
			// Actor->SetLockLocation(false);
			// EditorActorSubsystem->SetActorSelectionState(Actor.Get(), false);
			// EditorActorSubsystem->SetActorSelectionState(Actor.Get(), true);
		}
		else
		{
			for(FSelectionIterator It(*SelectedActors); It; ++It)
			{
				AActor* SelectedActor = Cast<AActor>( *It );
				if (SelectedActor)
				{
					SelectedActor->bLockLocation = false;
				}
				// SelectedActor->SetLockLocation(false);
			}

			// for(FSelectionIterator It(*SelectedActors); It; ++It)
			// {
			// 	AActor* SelectedActor = Cast<AActor>( *It );
			//
			// 	EditorActorSubsystem->SetActorSelectionState(SelectedActor, false);
			// 	EditorActorSubsystem->SetActorSelectionState(SelectedActor, true);
			// }
		}
		
		if(SceneOutliner.IsValid())
		{
			SceneOutliner->FullRefresh();
		}
		return;
	}
	
	return;
}

void FSceneOutlinerLockColumn::OnLockToggleStateChanged_LockSelection_SelectedActor(ECheckBoxState NewState, TWeakObjectPtr<AActor> Actor)
{
	FExtendSceneOutlinerModule& ExtendSceneOutlinerModule = 
		FModuleManager::LoadModuleChecked<FExtendSceneOutlinerModule>(TEXT("ExtendSceneOutliner"));
	
	// 当开关状态发生改变时，执行对应操作
	if(NewState == ECheckBoxState::Checked)
	{
		ExtendSceneOutlinerModule.LockActorSelection(Actor.Get());
		ExtendSceneOutlinerModule.SetActorSelectionState(Actor.Get(), false);
		return;
	}

	if(NewState == ECheckBoxState::Unchecked)
	{
		ExtendSceneOutlinerModule.UnlockActorSelection(Actor.Get());
		return;
	}

	return;
}

void FSceneOutlinerLockColumn::OnLockToggleStateChanged_LockSelection_SelectedActors(ECheckBoxState NewState, TWeakObjectPtr<AActor> Actor)
{
	FLevelEditorModule& LevelEditorModule = 
		FModuleManager::LoadModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));

	TSharedPtr<ISceneOutliner> SceneOutliner = 
		LevelEditorModule.GetFirstLevelEditor()->GetSceneOutliner();
	
	FExtendSceneOutlinerModule& ExtendSceneOutlinerModule = 
		FModuleManager::LoadModuleChecked<FExtendSceneOutlinerModule>(TEXT("ExtendSceneOutliner"));
	
	// 获取 ActorSelection
	USelection* SelectedActors = GEditor->GetSelectedActors();
	
	// SelectedActors->Num() == 0 当选择最顶层的Map时,Num=0;
	UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:Select %d Actors"),__FUNCTIONW__,__LINE__,SelectedActors->Num());

	// 多选存在问题;
	if(NewState == ECheckBoxState::Checked)
	{
		// 如果没有选中任何 Actor，仅发生了按钮的点击事件
		if(SelectedActors->Num() == 0)
		{
			ExtendSceneOutlinerModule.LockActorSelection(Actor.Get());
			ExtendSceneOutlinerModule.SetActorSelectionState(Actor.Get(),false);
		}
		else
		{
			// 第一次遍历添加Tag
			// 防止状态在运行过程被清除
			for(FSelectionIterator It(*SelectedActors); It; ++It)
			{
				AActor* SelectedActor = Cast<AActor>( *It );
				if (SelectedActor)
				{
					ExtendSceneOutlinerModule.LockActorSelection(SelectedActor);
				}
			}
			// 重新设置选择状态
			for(FSelectionIterator It(*SelectedActors); It; ++It)
			{
				AActor* SelectedActor = Cast<AActor>( *It );
				if (SelectedActor)
				{
					ExtendSceneOutlinerModule.SetActorSelectionState(SelectedActor,false);
				}
			}
		}
		
		// 设置完毕后刷新 SceneOutliner 重新生成图标
		if(SceneOutliner.IsValid())
		{
			UE_LOG(LogTemp,Warning,TEXT("---------------------------------------FLUSH-------------------------------------"));
			SceneOutliner->FullRefresh();
		}
 		
		return;
	}

	// 没有问题
	if(NewState == ECheckBoxState::Unchecked)
	{
		if(SelectedActors->Num() == 0)
		{
			ExtendSceneOutlinerModule.UnlockActorSelection(Actor.Get());
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:Cancel Select %d Call"),__FUNCTIONW__,__LINE__,SelectedActors->Num());
			for(FSelectionIterator It(*SelectedActors); It; ++It)
			{
				AActor* SelectedActor = Cast<AActor>( *It );
				if (SelectedActor)
				{
					ExtendSceneOutlinerModule.UnlockActorSelection(SelectedActor);
				}
			}
		}
		
		if(SceneOutliner.IsValid())
		{
			UE_LOG(LogTemp,Warning,TEXT("---------------------------------------FLUSH-------------------------------------"));
			SceneOutliner->FullRefresh();
		}
		return;
	}
	return;
}
