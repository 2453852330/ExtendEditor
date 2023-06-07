#include "MyClassCustomization.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "MyClass.h"

TSharedRef<IDetailCustomization> FMyClassCustomization::MakeInstance()
{
	return MakeShareable(new FMyClassCustomization());
}

void FMyClassCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	{
		// // 获取属性句柄
		// TSharedPtr<IPropertyHandle> SumPropertyHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(AMyClass, Sum));
		// TSharedPtr<IPropertyHandle> APropertyHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(AMyClass, A));
		// // 获取类别句柄，如果没有该类别则新建一个
		// IDetailCategoryBuilder& NewCat = DetailBuilder.EditCategory(TEXT("NewCategory"));
		//
		// NewCat.AddProperty(SumPropertyHandle);
		// DetailBuilder.HideProperty(APropertyHandle);
	}
	
	{
		// // 从DetailBuilder获取弱指针数组
		// TArray<TWeakObjectPtr<UObject>> Objects;
		// DetailBuilder.GetObjectsBeingCustomized(Objects);
		// // 设置MyObject。选择，并强转数组中的第一个指针为MyClass类
		// TWeakObjectPtr<AMyClass> MyObject = Cast<AMyClass>(Objects[0].Get());
		//
		// // 在细节面板中新建一个类别
		// IDetailCategoryBuilder& NewCat = DetailBuilder.EditCategory(TEXT("NewCategory"));
		// // 自定义该类的样式，将MyObject的名字显示出来
		// NewCat.AddCustomRow(FText())
		// [
		// 	SNew(STextBlock)
		// 	.Text(FText::FromName(MyObject->GetFName()))
		// ];
	}

	{
		// IDetailCategoryBuilder& AddItems = DetailBuilder.EditCategory(TEXT("Add Items"));
		// TSharedPtr<IPropertyHandle> APropertyHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(AMyClass, A));
		// TSharedPtr<IPropertyHandle> BPropertyHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(AMyClass, B));
		//
		// // 等同于DetailBuilder.HideProperty(APropertyHandle);
		// APropertyHandle->MarkHiddenByCustomization();
		// BPropertyHandle->MarkHiddenByCustomization();
		//
		// AddItems
		// .AddCustomRow(FText())
		// [
		// 	SNew(SHorizontalBox)
		// 	+ SHorizontalBox::Slot()
		// 	[
		// 		SNew(SVerticalBox)
		// 		+ SVerticalBox::Slot()
		// 		[APropertyHandle->CreatePropertyNameWidget()]
		// 		+ SVerticalBox::Slot()
		// 		[APropertyHandle->CreatePropertyValueWidget()]
		// 	]
		// 	+ SHorizontalBox::Slot()
		// 	[
		// 		SNew(SVerticalBox)
		// 		+ SVerticalBox::Slot()
		// 		[BPropertyHandle->CreatePropertyNameWidget()]
		// 		+ SVerticalBox::Slot()
		// 		[BPropertyHandle->CreatePropertyValueWidget()]
		// 	]
		// ];
	}

	{
		TArray<TWeakObjectPtr<UObject>> Objects;
		DetailBuilder.GetObjectsBeingCustomized(Objects);

		// 只允许在选择一个MyClass时进行加法计算
		if(Objects.Num() != 1)
		{
			return;
		}
	
		TWeakObjectPtr<AMyClass> MyObject = Cast<AMyClass>(Objects[0].Get());
	
	
		IDetailCategoryBuilder& AddItems = DetailBuilder.EditCategory(TEXT("Add Items"));
		TSharedPtr<IPropertyHandle> APropertyHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(AMyClass, A));
		TSharedPtr<IPropertyHandle> BPropertyHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(AMyClass, B));


		// 通过简单的Lambda代理实现运算
		auto OnPropertyChanged = [=]{MyObject->Sum = MyObject->A + MyObject->B;};
		APropertyHandle->SetOnPropertyValueChanged(FSimpleDelegate::CreateLambda(OnPropertyChanged));
		BPropertyHandle->SetOnPropertyValueChanged(FSimpleDelegate::CreateLambda(OnPropertyChanged));

	}
}

// 隐藏一个属性
// DetailBuilder.HideProperty(Prop);

// 隐藏一个类别
// DetailBuilder.HideCategory(TEXT("NewCategory"));

// 将一个属性移动到一个类别中
// NewCat.AddProperty(Prop);