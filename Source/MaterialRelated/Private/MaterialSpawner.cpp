// Fill out your copyright notice in the Description page of Project Settings.


#include "MaterialSpawner.h"

#include "AssetToolsModule.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "Factories/MaterialFactoryNew.h"
#include "Factories/MaterialInstanceConstantFactoryNew.h"
#include "Materials/MaterialExpressionCollectionParameter.h"
#include "Materials/MaterialExpressionConstant.h"
#include "Materials/MaterialExpressionMultiply.h"
#include "Materials/MaterialExpressionVectorParameter.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialParameterCollection.h"

void UMaterialSpawner::CreateMaterial(const FString& AssetName)
{
	// 获取选中的路径视图的文件夹
	FContentBrowserModule& ContentBrowserModule = 
		FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	
	TArray<FString> PathViewFolders;
	ContentBrowserModule.Get().GetSelectedPathViewFolders(PathViewFolders);

	// 创建 MaterialAsset
	FAssetToolsModule& AssetToolsModule = 
		FModuleManager::LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools"));

	UMaterialFactoryNew* MaterialFactory = NewObject<UMaterialFactoryNew>();
	
	UObject* CreatedObject = AssetToolsModule.Get().CreateAsset(AssetName, PathViewFolders[0],
		UMaterial::StaticClass(), MaterialFactory);

	// 保存 MaterialAsset
	// FString AssetPath = CreatedObject->GetPathName();
	// UEditorAssetLibrary::SaveAsset(AssetPath);
}

void UMaterialSpawner::CreateMaterialInstance(UMaterialInterface* ParentMaterial, const FString& AssetName)
{
	// 获取选中的路径视图的文件夹
	FContentBrowserModule& ContentBrowserModule = 
		FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");

	TArray<FString> PathViewFolders;
	ContentBrowserModule.Get().GetSelectedPathViewFolders(PathViewFolders);

	// 创建 Material Instance
	FAssetToolsModule& AssetToolsModule = 
		FModuleManager::LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools"));

	UMaterialInstanceConstantFactoryNew* MaterialInstanceConstantFactory = 
		NewObject<UMaterialInstanceConstantFactoryNew>();
	
	UObject* MaterialInstance = AssetToolsModule.Get().CreateAsset(AssetName, PathViewFolders[0],
		UMaterialInstanceConstant::StaticClass(), MaterialInstanceConstantFactory);

	// 设置 Parent
	if(UMaterialInstanceConstant* CreatedMaterialInstance = 
		Cast<UMaterialInstanceConstant>(MaterialInstance))
	{
		CreatedMaterialInstance->SetParentEditorOnly(ParentMaterial);
		CreatedMaterialInstance->PostEditChange();
		ParentMaterial->PostEditChange();
	}
}

void UMaterialSpawner::SetMaterialParameter()
{
	{
		// UMaterial* Material = ***;
		// Material->BlendMode = EBlendMode::BLEND_Masked;
		// Parent->TwoSided = true;
	}
	{
		// UMaterial* Material = ***;
		// UMaterialInstanceConstant* MaterialInstance = ***;
		//
		// // 修改标量参数
		// UMaterial->SetScalarParameterValueEditorOnly(...);
		// // 修改矢量参数
		// UMaterialInstanceConstant->SetVectorParameterValueEditorOnly(...);
		// // 修改纹理参数
		// UMaterialInstanceConstant->SetTextureParameterValueEditorOnly(...);
	}

	{
		// 在当前路径视图文件夹中创建 “MI_SetMaterialParameter”
		FContentBrowserModule& ContentBrowserModule = 
			FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	
		TArray<FString> PathViewFolders;
		ContentBrowserModule.Get().GetSelectedPathViewFolders(PathViewFolders);
	
		FAssetToolsModule& AssetToolsModule = 
			FModuleManager::LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools"));
	
		UMaterialInstanceConstantFactoryNew* MaterialInstanceConstantFactory = 
			NewObject<UMaterialInstanceConstantFactoryNew>();
	
		UObject* MaterialInstance = 
			AssetToolsModule.Get().CreateAsset("MI_SetMaterialParameter", PathViewFolders[0],
			UMaterialInstanceConstant::StaticClass(), MaterialInstanceConstantFactory);

		// 从外部导入 Texture 资源。这次我们也直接从已有资产获取 Material
		UMaterial* Parent = 
			LoadObject<UMaterial>(nullptr, TEXT("Material'/Game/Material/M_Parent.M_Parent'"));
		UTexture* Texture = 
			LoadObject<UTexture>(nullptr, TEXT("Texture2D'/Game/Material/DefaultVolumeTexture2D.DefaultVolumeTexture2D'"));

		if(UMaterialInstanceConstant* CreatedMaterialInstance = 
			Cast<UMaterialInstanceConstant>(MaterialInstance))
		{
			CreatedMaterialInstance->SetParentEditorOnly(Parent);
			CreatedMaterialInstance->PostEditChange();
			Parent->PostEditChange();

			// 修改 Material 属性
			Parent->BlendMode = EBlendMode::BLEND_Masked;	// 修改为 Mask 模式
			Parent->TwoSided = true;			// 设置为双面显示
			Parent->PostEditChange();

			// 修改 Scale 参数
			CreatedMaterialInstance->SetScalarParameterValueEditorOnly(
				FMaterialParameterInfo(TEXT("RoughnessValue")), 0);
			// 修改 Vector 参数
			CreatedMaterialInstance->SetVectorParameterValueEditorOnly(
				FMaterialParameterInfo(TEXT("EmissiveColor")), 
				FLinearColor(0.2f, 0.0f, 0.0f));
			// 修改 Texture 参数
			CreatedMaterialInstance->SetTextureParameterValueEditorOnly(
				FMaterialParameterInfo(TEXT("BaseColorTexture")),Texture);
			CreatedMaterialInstance->PostEditChange();
		}
	}
}

void UMaterialSpawner::EditMaterial(UMaterial* Material)
{
	/*
	 * 创建和设置 Node
	 */
	
	// 创建一个常数Node,并设置值为0.5
	UMaterialExpressionConstant* ConstantExpression = NewObject<UMaterialExpressionConstant>(Material);
	ConstantExpression->R = 0.5f;

	// 创建 TextureSample node ,并设置图片
	UMaterialExpressionTextureSample* TextureExpression = 
		NewObject<UMaterialExpressionTextureSample>(Material);
	TextureExpression->Texture = 
		LoadObject<UTexture>(
			nullptr, 
			TEXT("Texture2D'/Game/Material/DefaultVolumeTexture2D.DefaultVolumeTexture2D'"));
	
	// 创建并设置 Constant parameter node
	// 创建一个参数节点
	UMaterialExpressionVectorParameter* VectorParameter = 
		NewObject<UMaterialExpressionVectorParameter>(Material);
	VectorParameter->ParameterName = TEXT("VectorParameter");
	VectorParameter->DefaultValue = FLinearColor(0.2f, 0.0f, 0.5f);
	

	// 准备 FExpressionInput，稍后赋值给 MultiplyExpression 的 A 输入
	FExpressionInput TextureExpressionInput;
	TextureExpressionInput.Expression = TextureExpression;

	// 创建并设置 Multiply node ,乘法节点
	UMaterialExpressionMultiply* MultiplyExpression = NewObject<UMaterialExpressionMultiply>(Material);
	MultiplyExpression->A = TextureExpressionInput;
	// 用这种方式可以选择要连接的输出编号
	MultiplyExpression->B.Connect(3, VectorParameter);

	/*
	 * 设置 node position
	 */
	TextureExpression->MaterialExpressionEditorX = -600;
	TextureExpression->MaterialExpressionEditorY = 0;
	
	VectorParameter->MaterialExpressionEditorX = -600;
	VectorParameter->MaterialExpressionEditorY = 240;

	MultiplyExpression->MaterialExpressionEditorX = -300;
	MultiplyExpression->MaterialExpressionEditorY = 0;
	
	ConstantExpression->MaterialExpressionEditorX = -300;
	ConstantExpression->MaterialExpressionEditorY = 240;
	
	/*
	 * 将所有 Node 添加到材质，并连接材质输出
	 */
	Material->Expressions.Add(ConstantExpression);
	Material->Expressions.Add(TextureExpression);
	Material->Expressions.Add(MultiplyExpression);
	Material->Expressions.Add(VectorParameter);
	
	Material->BaseColor.Expression = MultiplyExpression;
	Material->BaseColor.Mask = 0;
	Material->Metallic.Expression = ConstantExpression;
	// 用这种方式可以选择要连接的输出编号
	Material->Roughness.Connect(2, VectorParameter);
	
	Material->PostEditChange();
	Material->MarkPackageDirty();
}

void UMaterialSpawner::AddMaterialFunction(UMaterial* Material)
{
	// 载入 MaterialFunction(MF_Addtion)
	UMaterialFunction* MyFunction = 
		LoadObject<UMaterialFunction>(
			nullptr, TEXT("MaterialFunction'/Game/MF_Addtion.MF_Addtion'"));

	// 创建 UMaterialExpressionMaterialFunctionCall，对应材质蓝图中的 MaterialFunctionCall
	// 将其 MaterialFuntion 设置为 MF_Addtion
	UMaterialExpressionMaterialFunctionCall* MyFunctionCall = 
		NewObject<UMaterialExpressionMaterialFunctionCall>(Material);
	MyFunctionCall->SetMaterialFunction(MyFunction);
	MyFunctionCall->MaterialExpressionEditorX = -300;
	MyFunctionCall->MaterialExpressionEditorY = 0;

	// 准备两个 Constant 节点作为输入
	UMaterialExpressionConstant* ConstantA = NewObject<UMaterialExpressionConstant>(Material);
	ConstantA->R = 10;
	ConstantA->MaterialExpressionEditorX = -600;
	ConstantA->MaterialExpressionEditorY = 0;
	
	UMaterialExpressionConstant* ConstantB = NewObject<UMaterialExpressionConstant>(Material);
	ConstantB->R = 5;
	ConstantB->MaterialExpressionEditorX = -600;
	ConstantB->MaterialExpressionEditorY = 100;
	
	// 在 UE5.0.3 中尚不支持 UMaterialExpressionMaterialFunctionCall::GetInputByName()
	// 因此我们需要够通过遍历的方法来找到对应名称的 Input 并设置 Expression
	TArray<FExpressionInput*> MyFunctionInputs = MyFunctionCall->GetInputs();
	
	for(FExpressionInput* MyFunctionInput : MyFunctionInputs)
	{
		if(MyFunctionInput->InputName == TEXT("A"))
		{
			MyFunctionInput->Expression = ConstantA;
			break;
		}
	}

	for(FExpressionInput* MyFunctionInput : MyFunctionInputs)
	{
		if(MyFunctionInput->InputName == TEXT("B"))
		{
			MyFunctionInput->Expression = ConstantB;
			break;
		}
	}

	// 将所有 Node 添加到材质，并连接材质输出
	Material->Expressions.Add(ConstantA);
	Material->Expressions.Add(ConstantB);
	Material->Expressions.Add(MyFunctionCall);

	Material->BaseColor.Expression = MyFunctionCall;

	Material->PostEditChange();
	Material->MarkPackageDirty();
}

void UMaterialSpawner::AddMaterialParameterCollection(UMaterial* Material)
{
	// 载入 UMaterialParameterCollection (MPC_MyParameters)
	UMaterialParameterCollection* MyMPC = 
		LoadObject<UMaterialParameterCollection>(
			nullptr, TEXT("MaterialParameterCollection'/Game/MPC_MyParameters.MPC_MyParameters'"));
	
	// 创建 UMaterialExpressionCollectionParameter 节点
	UMaterialExpressionCollectionParameter* MPC_Node = 
		NewObject<UMaterialExpressionCollectionParameter>(Material);
	MPC_Node->Collection = MyMPC;
	MPC_Node->ParameterName = FName(TEXT("MyTestColor"));
	// 应用修改
	MPC_Node->PostEditChange();

	// 添加新参数集节点
	UMaterialExpressionCollectionParameter * MPC_Node2=
		NewObject<UMaterialExpressionCollectionParameter>(Material);
	MPC_Node2->Collection = MyMPC;
	MPC_Node2->ParameterName = FName(TEXT("MyTestValue"));
	MPC_Node2->PostEditChange();

	// multiply node
	UMaterialExpressionMultiply * Mul_Node =
		NewObject<UMaterialExpressionMultiply>(Material);
	
	MPC_Node->ConnectExpression(&Mul_Node->A,0);
	MPC_Node2->ConnectExpression(&Mul_Node->B,0);
	
	
	// 将所有 Node 添加到材质，并连接材质输出
	Material->Expressions.Add(MPC_Node);
	Material->Expressions.Add(MPC_Node2);
	Material->Expressions.Add(Mul_Node);
	Material->BaseColor.Expression = Mul_Node;

	Material->PostEditChange();
	Material->MarkPackageDirty();
	
}
