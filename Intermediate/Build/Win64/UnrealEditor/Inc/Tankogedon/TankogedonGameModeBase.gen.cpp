// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Tankogedon/TankogedonGameModeBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTankogedonGameModeBase() {}
// Cross Module References
	TANKOGEDON_API UClass* Z_Construct_UClass_ATankogedonGameModeBase_NoRegister();
	TANKOGEDON_API UClass* Z_Construct_UClass_ATankogedonGameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_Tankogedon();
// End Cross Module References
	void ATankogedonGameModeBase::StaticRegisterNativesATankogedonGameModeBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ATankogedonGameModeBase);
	UClass* Z_Construct_UClass_ATankogedonGameModeBase_NoRegister()
	{
		return ATankogedonGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_ATankogedonGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATankogedonGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_Tankogedon,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATankogedonGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "TankogedonGameModeBase.h" },
		{ "ModuleRelativePath", "TankogedonGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATankogedonGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATankogedonGameModeBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ATankogedonGameModeBase_Statics::ClassParams = {
		&ATankogedonGameModeBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_ATankogedonGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ATankogedonGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ATankogedonGameModeBase()
	{
		if (!Z_Registration_Info_UClass_ATankogedonGameModeBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ATankogedonGameModeBase.OuterSingleton, Z_Construct_UClass_ATankogedonGameModeBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ATankogedonGameModeBase.OuterSingleton;
	}
	template<> TANKOGEDON_API UClass* StaticClass<ATankogedonGameModeBase>()
	{
		return ATankogedonGameModeBase::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATankogedonGameModeBase);
	struct Z_CompiledInDeferFile_FID_Tankogedon_Source_Tankogedon_TankogedonGameModeBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Tankogedon_Source_Tankogedon_TankogedonGameModeBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ATankogedonGameModeBase, ATankogedonGameModeBase::StaticClass, TEXT("ATankogedonGameModeBase"), &Z_Registration_Info_UClass_ATankogedonGameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ATankogedonGameModeBase), 832376055U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Tankogedon_Source_Tankogedon_TankogedonGameModeBase_h_1825969087(TEXT("/Script/Tankogedon"),
		Z_CompiledInDeferFile_FID_Tankogedon_Source_Tankogedon_TankogedonGameModeBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Tankogedon_Source_Tankogedon_TankogedonGameModeBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
