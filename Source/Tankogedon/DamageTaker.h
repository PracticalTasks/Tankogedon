// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameStruct.h"
#include "DamageTaker.generated.h"

UINTERFACE(MinimalAPI)
class UDamageTaker : public UInterface
{
	GENERATED_BODY()
};

class TANKOGEDON_API IDamageTaker
{
	GENERATED_BODY()
public:
	void virtual TakeDamage(FDamageData DamageData) = 0;
};
