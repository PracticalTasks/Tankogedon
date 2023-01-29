// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "GameStruct.generated.h"

UENUM(BlueprintType)
enum class ECannonType : uint8
{
	FireTrace = 0 UMETA(DisplayName = "Use trace"),
	FireProjecttile = 1 UMETA(DisplayName = "Projectile"),
	FireAltProjecttile = 2 UMETA(DisplayName = "Use alter projectile"),
};

USTRUCT()
struct FDamageData
{
	GENERATED_BODY()
	UPROPERTY()
	float DamageValue;
	UPROPERTY()
	AActor* Instigator;
	UPROPERTY()
	AActor* DamageMaker;
};

UCLASS()
class TANKOGEDON_API UGameStruct : public UObject
{
	GENERATED_BODY()
	
};
