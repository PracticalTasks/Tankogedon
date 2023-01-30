// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef TANKOGEDON_TankPawn_generated_h
#error "TankPawn.generated.h already included, missing '#pragma once' in TankPawn.h"
#endif
#define TANKOGEDON_TankPawn_generated_h

#define FID_Tankogedon_Source_Tankogedon_TankPawn_h_17_SPARSE_DATA
#define FID_Tankogedon_Source_Tankogedon_TankPawn_h_17_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execDie);


#define FID_Tankogedon_Source_Tankogedon_TankPawn_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execDie);


#define FID_Tankogedon_Source_Tankogedon_TankPawn_h_17_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesATankPawn(); \
	friend struct Z_Construct_UClass_ATankPawn_Statics; \
public: \
	DECLARE_CLASS(ATankPawn, APawn, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Tankogedon"), NO_API) \
	DECLARE_SERIALIZER(ATankPawn)


#define FID_Tankogedon_Source_Tankogedon_TankPawn_h_17_INCLASS \
private: \
	static void StaticRegisterNativesATankPawn(); \
	friend struct Z_Construct_UClass_ATankPawn_Statics; \
public: \
	DECLARE_CLASS(ATankPawn, APawn, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Tankogedon"), NO_API) \
	DECLARE_SERIALIZER(ATankPawn)


#define FID_Tankogedon_Source_Tankogedon_TankPawn_h_17_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ATankPawn(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ATankPawn) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATankPawn); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATankPawn); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ATankPawn(ATankPawn&&); \
	NO_API ATankPawn(const ATankPawn&); \
public:


#define FID_Tankogedon_Source_Tankogedon_TankPawn_h_17_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ATankPawn(ATankPawn&&); \
	NO_API ATankPawn(const ATankPawn&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATankPawn); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATankPawn); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ATankPawn)


#define FID_Tankogedon_Source_Tankogedon_TankPawn_h_13_PROLOG
#define FID_Tankogedon_Source_Tankogedon_TankPawn_h_17_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Tankogedon_Source_Tankogedon_TankPawn_h_17_SPARSE_DATA \
	FID_Tankogedon_Source_Tankogedon_TankPawn_h_17_RPC_WRAPPERS \
	FID_Tankogedon_Source_Tankogedon_TankPawn_h_17_INCLASS \
	FID_Tankogedon_Source_Tankogedon_TankPawn_h_17_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_Tankogedon_Source_Tankogedon_TankPawn_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Tankogedon_Source_Tankogedon_TankPawn_h_17_SPARSE_DATA \
	FID_Tankogedon_Source_Tankogedon_TankPawn_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Tankogedon_Source_Tankogedon_TankPawn_h_17_INCLASS_NO_PURE_DECLS \
	FID_Tankogedon_Source_Tankogedon_TankPawn_h_17_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> TANKOGEDON_API UClass* StaticClass<class ATankPawn>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Tankogedon_Source_Tankogedon_TankPawn_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
