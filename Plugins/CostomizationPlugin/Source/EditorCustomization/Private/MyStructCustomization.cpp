#include "MyStructCustomization.h"

#include "CustomType.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"


TSharedRef<IPropertyTypeCustomization> FMyStructCustomization::MakeInstance()
{
	return MakeShareable(new FMyStructCustomization());
}

void FMyStructCustomization::CustomizeHeader(
	TSharedRef<IPropertyHandle> PropertyHandle,
	FDetailWidgetRow& HeaderRow,
	IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	{
		// HeaderRow.NameContent()[PropertyHandle->CreatePropertyNameWidget()];
	}

	{
		// // 获取Name属性的句柄
		// TSharedPtr<IPropertyHandle> NamePropertyHandle = 
		// PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FMyStruct, Name));
		//
		// // 在使用句柄之前，检查句柄是否为空
		// check(NamePropertyHandle.IsValid());
		//
		// // 构建Slate
		// HeaderRow
		// // 每一个默认Content都分为NameContent和ValueContent
		// // NameContent和ValueContent之间由一道分隔线区分：
		// // [ Struct Value Category      ]
		// // [ NameContent | ValueContent ] ( HeaderRow )
		// // [      ...    |      ...     ] ( ChildrenRow )
		// .NameContent()[PropertyHandle->CreatePropertyNameWidget()]
		// .ValueContent()
		// .HAlign(HAlign_Fill)
		// [
		// 	SNew(SBox)
		// 	[
		// 		SNew(SHorizontalBox)
		// 		+ SHorizontalBox::Slot()
		// 		.HAlign(HAlign_Left)
		// 		.AutoWidth()
		// 		.Padding(5.0f, 0.0f)
		// 		[
		// 			NamePropertyHandle->CreatePropertyNameWidget()
		// 		]
		// 		+ SHorizontalBox::Slot()
		// 		.FillWidth(1.0f)
		// 		[
		// 			NamePropertyHandle->CreatePropertyValueWidget()
		// 		]
		// 	]
		// ];
	}
	
}

void FMyStructCustomization::CustomizeChildren(
	TSharedRef<IPropertyHandle> PropertyHandle,
	IDetailChildrenBuilder& ChildBuilder,
	IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	TSharedPtr<IPropertyHandle> PrefixPropertyHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FMyStruct, Prefix));
	TSharedPtr<IPropertyHandle> BaseNamePropertyHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FMyStruct, BaseName));
	TSharedPtr<IPropertyHandle> SuffixPropertyHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FMyStruct, Suffix));

	check(PrefixPropertyHandle.IsValid() && BaseNamePropertyHandle.IsValid() && SuffixPropertyHandle.IsValid());

	ChildBuilder.AddCustomRow(FText())
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.Padding(5.0f, 0.0f)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			[PrefixPropertyHandle->CreatePropertyNameWidget()]
			+ SVerticalBox::Slot()
			[PrefixPropertyHandle->CreatePropertyValueWidget()]
		]
		+ SHorizontalBox::Slot()
		.Padding(5.0f, 0.0f)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			[BaseNamePropertyHandle->CreatePropertyNameWidget()]
			+ SVerticalBox::Slot()
			[BaseNamePropertyHandle->CreatePropertyValueWidget()]
		]
		+ SHorizontalBox::Slot()
		.Padding(5.0f, 0.0f)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			[SuffixPropertyHandle->CreatePropertyNameWidget()]
			+ SVerticalBox::Slot()
			[SuffixPropertyHandle->CreatePropertyValueWidget()]
		]
	];
}
