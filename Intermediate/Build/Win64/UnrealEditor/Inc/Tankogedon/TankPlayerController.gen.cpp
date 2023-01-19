// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Tankogedon/TankPlayerController.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTankPlayerController() {}
// Cross Module References
	TANKOGEDON_API UClass* Z_Construct_UClass_ATankPlayerController_NoRegister();
	TANKOGEDON_API UClass* Z_Construct_UClass_ATankPlayerController();
	ENGINE_API UClass* Z_Construct_UClass_APlayerController();
	UPackage* Z_Construct_UPackage__Script_Tankogedon();
	TANKOGEDON_API UClass* Z_Construct_UClass_ATankPawn_NoRegister();
// End Cross Module References
	void ATankPlayerController::StaticRegisterNativesATankPlayerController()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ATankPlayerController);
	UClass* Z_Construct_UClass_ATankPlayerController_NoRegister()
	{
		return ATankPlayerController::StaticClass();
	}
	struct Z_Construct_UClass_ATankPlayerController_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TankPawn_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_TankPawn;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATankPlayerController_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APlayerController,
		(UObject* (*)())Z_Construct_UPackage__Script_Tankogedon,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATankPlayerController_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "TankPlayerController.h" },
		{ "ModuleRelativePath", "TankPlayerController.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATankPlayerController_Statics::NewProp_TankPawn_MetaData[] = {
		{ "ModuleRelativePath", "TankPlayerController.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATankPlayerController_Statics::NewProp_TankPawn = { "TankPawn", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ATankPlayerController, TankPawn), Z_Construct_UClass_ATankPawn_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ATankPlayerController_Statics::NewProp_TankPawn_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ATankPlayerController_Statics::NewProp_TankPawn_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ATankPlayerController_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATankPlayerController_Statics::NewProp_TankPawn,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATankPlayerController_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATankPlayerController>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ATankPlayerController_Statics::ClassParams = {
		&ATankPlayerController::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ATankPlayerController_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ATankPlayerController_Statics::PropPointers),
		0,
		0x009002A4u,
		METADATA_PARAMS(Z_Construct_UClass_ATankPlayerController_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ATankPlayerController_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ATankPlayerController()
	{
		if (!Z_Registration_Info_UClass_ATankPlayerController.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ATankPlayerController.OuterSingleton, Z_Construct_UClass_ATankPlayerController_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ATankPlayerController.OuterSingleton;
	}
	template<> TANKOGEDON_API UClass* StaticClass<ATankPlayerController>()
	{
		return ATankPlayerController::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATankPlayerController);
	struct Z_CompiledInDeferFile_FID_Tankogedon_Source_Tankogedon_TankPlayerController_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Tankogedon_Source_Tankogedon_TankPlayerController_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ATankPlayerController, ATankPlayerController::StaticClass, TEXT("ATankPlayerController"), &Z_Registration_Info_UClass_ATankPlayerController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ATankPlayerController), 1171174284U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Tankogedon_Source_Tankogedon_TankPlayerController_h_229842424(TEXT("/Script/Tankogedon"),
		Z_CompiledInDeferFile_FID_Tankogedon_Source_Tankogedon_TankPlayerController_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Tankogedon_Source_Tankogedon_TankPlayerController_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
