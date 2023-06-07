#pragma once

#include "ISceneOutlinerColumn.h"
#include "SSceneOutliner.h"
#include "SceneOutliner/Public/SceneOutlinerFwd.h"

class FSceneOutlinerLockColumn : public ISceneOutlinerColumn
{
public:

	FSceneOutlinerLockColumn(ISceneOutliner& SceneOutliner){}
	
	static FName GetID() {return FName("SceneOutlinerExtendColumn");}

	virtual FName GetColumnID() override {return GetID();}

	// 在标题头添加新 Widget
	virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;

	// 在项目行添加新 Widget
	// 这个UE5的
	// virtual const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;
	// 下面是UE4
	virtual const TSharedRef<SWidget> ConstructRowWidget(SceneOutliner::FTreeItemRef TreeItem, const STableRow<SceneOutliner::FTreeItemPtr>& Row) override;

	// 1.基础测试绑定函数
	void OnLockToggleStateChanged(ECheckBoxState NewState, TWeakObjectPtr<AActor> Actor);

	// 2.锁定移动绑定函数
	// 替代上面事件的新函数
	void OnLockToggleStateChanged_LockMovement_SelectedActor(ECheckBoxState NewState, TWeakObjectPtr<AActor> Actor);

	// 3.锁定移动函数,批量多个
	// 替代上面事件的新函数
	void OnLockToggleStateChanged_LockMovement_SelectedActors(ECheckBoxState NewState, TWeakObjectPtr<AActor> Actor);

	// 4.单个锁定选择
	// 替代上面事件的新函数
	void OnLockToggleStateChanged_LockSelection_SelectedActor(ECheckBoxState NewState, TWeakObjectPtr<AActor> Actor);

	// 5.批量锁定选择
	// 替代上面事件的新函数
	void OnLockToggleStateChanged_LockSelection_SelectedActors(ECheckBoxState NewState, TWeakObjectPtr<AActor> Actor);
	
};