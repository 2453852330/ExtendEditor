#include "CustomNormalDistributionImportFactory.h"

#include "CustomNormalDistribution.h"
#include "EditorFramework/AssetImportData.h"
#include "Misc/FileHelper.h"

UCustomNormalDistributionImportFactory::UCustomNormalDistributionImportFactory()
{
	SupportedClass = UCustomNormalDistribution::StaticClass();
	// 必须关闭可新建
	// 添加可导入的文件名后缀
	// 开启可导入
	// 导入的文件格式为 Text（另一种格式为二进制）
	bCreateNew = false;
	Formats.Add(TEXT("cnd;Custom Normal Distribution"));
	bEditorImport = true;
	bText = true;
}

UObject* UCustomNormalDistributionImportFactory::FactoryCreateText(
	UClass* InClass, UObject* InParent, FName InName,
	EObjectFlags Flags, UObject* Context,
	const TCHAR* Type,// 后缀名
	const TCHAR*& Buffer,// 文本内容
	const TCHAR* BufferEnd, FFeedbackContext* Warn)
{
	GEditor->GetEditorSubsystem<UImportSubsystem>()->OnAssetPreImport.Broadcast(this, InClass, InParent, InName, Type);

	// 检查传入的类型和后缀名
	if (InClass != UCustomNormalDistribution::StaticClass() 
		|| FCString::Stricmp(Type, TEXT("cnd")) != 0) return nullptr;
	// 手动创建一个UCustomNormalDistribution对象
	UCustomNormalDistribution* Data = CastChecked<UCustomNormalDistribution>(
		NewObject<UCustomNormalDistribution>(InParent, InName, Flags));

	// 从文件获取值
	Data->Mean = FCString::Atof(*GetValueFromFile(Buffer, "[MySection]", "Mean"));
	Data->StandardDeviation = FCString::Atof(*GetValueFromFile(Buffer, "[MySection]", "StandardDeviation"));

	// 从文件获取值的另一种方式。我们特意将文件内容的书写格式与.ini相似，所以也可以借用.ini方式处理。
	// FConfigCacheIni Config(EConfigCacheType::Temporary);
	// Config.LoadFile(CurrentFilename);
	// Config.GetFloat(TEXT("MySection"), TEXT("Mean"), Data->Mean, CurrentFilename);
	// Config.GetFloat(TEXT("MySection"), TEXT("StandardDeviation"), Data->StandardDeviation, CurrentFilename);

	// 储存导入的路径
	Data->SourceFilePath = UAssetImportData::SanitizeImportFilename(CurrentFilename, Data->GetPackage());

	GEditor->GetEditorSubsystem<UImportSubsystem>()->OnAssetPostImport.Broadcast(this, Data);
	
	return Data;
}

bool UCustomNormalDistributionImportFactory::FactoryCanImport(const FString& Filename)
{
	// 通过后缀名检测能否导入?
	return FPaths::GetExtension(Filename).Equals(TEXT("cnd"));
}

FString UCustomNormalDistributionImportFactory::GetValueFromFile(const TCHAR*& Buffer, FString SectionName, FString VarName)
{
	FString Str(Buffer);

	Str = Str.Replace(TEXT("\r"), TEXT(""));
	
	TArray<FString> Lines;
	Str.ParseIntoArray(Lines, TEXT("\n"), true);
	
	bool bInSection = false;
	
	for (FString Line : Lines)
	{
		if (Line == SectionName)
		{
			bInSection = true;
		}
		else if (Line.StartsWith("[") && Line.EndsWith("]"))
		{
			bInSection = false;
		}

		if (bInSection)
		{
			int32 Pos = Line.Find("=");
			if (Pos != INDEX_NONE)
			{
				FString Name = Line.Left(Pos);
				FString Value = Line.Mid(Pos + 1);

				if (Name == VarName)
				{
					return Value;
				}
			}
		}
	}
	
	return "";
}

/*************************************** Reimport *************************************/
// 需要去ActionBase给右键菜单添加重新导入按钮

bool UCustomNormalDistributionImportFactory::CanReimport(UObject* Obj, TArray<FString>& OutFilenames)
{
	UCustomNormalDistribution* Data = Cast<UCustomNormalDistribution>(Obj);
	if (Data)
	{
		OutFilenames.Add(UAssetImportData::ResolveImportFilename(
			Data->SourceFilePath, Data->GetPackage()));
		return true;
	}
	return false;
}

void UCustomNormalDistributionImportFactory::SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths)
{
	UCustomNormalDistribution* Data = Cast<UCustomNormalDistribution>(Obj);
	if (Data && ensure(NewReimportPaths.Num() == 1))
	{
		Data->SourceFilePath = 
			UAssetImportData::SanitizeImportFilename(NewReimportPaths[0], Data->GetPackage());
	}
}

EReimportResult::Type UCustomNormalDistributionImportFactory::Reimport(UObject* Obj)
{
	UCustomNormalDistribution* Data = Cast<UCustomNormalDistribution>(Obj);
	if (!Data)
	{
		return EReimportResult::Failed;
	}

	const FString Filename = 
		UAssetImportData::ResolveImportFilename(Data->SourceFilePath, Data->GetPackage());
	if (!FPaths::GetExtension(Filename).Equals(TEXT("cnd")))
	{
		return EReimportResult::Failed;
	}

	CurrentFilename = Filename;
	FString LoadedData;
	if (FFileHelper::LoadFileToString(LoadedData, *CurrentFilename))
	{
		const TCHAR* LoadedDataChar = *LoadedData;
		Data->Modify();
		Data->MarkPackageDirty();

		Data->Mean = FCString::Atof(*GetValueFromFile(LoadedDataChar, "[MySection]", "Mean"));
		Data->StandardDeviation = 
			FCString::Atof(*GetValueFromFile(LoadedDataChar, "[MySection]", "StandardDeviation"));

		Data->SourceFilePath = 
			UAssetImportData::SanitizeImportFilename(CurrentFilename, Data->GetPackage());
	}
	return EReimportResult::Succeeded;
}

