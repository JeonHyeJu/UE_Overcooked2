// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/OC2Global.h"
#include "AssetRegistry/AssetRegistryModule.h"

void UOC2Global::GetAssetPackageName(UClass* Class, const FString& AssetName, FString& Path)
{
	TArray<FAssetData> AllAssetData = GetAssetDataArray(Class);

	FName CheckAssetName = FName(AssetName);

	for (const FAssetData& AssetData : AllAssetData)
	{
		if (AssetData.AssetName == CheckAssetName)
		{
			Path = AssetData.PackageName.ToString();
			return;
		}
	}
}

TArray<FAssetData> UOC2Global::GetAssetDataArray(UClass* Class)
{
	TArray<FAssetData> MapList;


	if (false == FModuleManager::Get().IsModuleLoaded("AssetRegistry"))
	{
		return MapList;
	}

	IAssetRegistry& AssetRegistry = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();

	// Asset ��Ȳ�� ���ؼ� ���� �ε带 ���� �ʾҴ��� ����.
	if (true == AssetRegistry.IsLoadingAssets())
	{
		return MapList;
	}

	if (AssetRegistry.GetAssetsByClass(Class->GetClassPathName(), MapList))
	{
		return MapList;
	}

	return MapList;
}
