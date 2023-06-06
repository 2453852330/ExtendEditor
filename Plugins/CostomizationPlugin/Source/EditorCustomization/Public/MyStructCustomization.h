#pragma once

class FMyStructCustomization : public IPropertyTypeCustomization
{
public:

	// MakeInstance 是一个辅助函数，用于快速实例化我们的自定义类
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	// CustomizeHeader 用于自定义上图红色部分的行为
	virtual void CustomizeHeader(
		TSharedRef<IPropertyHandle> PropertyHandle,
		FDetailWidgetRow& HeaderRow,
		IPropertyTypeCustomizationUtils& CustomizationUtils) override;

	// CustomizeChildren 用于自定义上图绿色部分的行为
	virtual void CustomizeChildren(
		TSharedRef<IPropertyHandle> PropertyHandle,
		IDetailChildrenBuilder& ChildBuilder,
		IPropertyTypeCustomizationUtils& CustomizationUtils) override;
};