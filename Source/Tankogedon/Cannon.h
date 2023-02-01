// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStruct.h"
#include "Components/ArrowComponent.h"
//#include "TraceInsights/Public/Insights/Common/PaintUtils.h"
#include "Cannon.generated.h"

UCLASS()
class TANKOGEDON_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:	
	ACannon();

	void Fire();
	void FireSpecial();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire param")
	ECannonType CannonType = ECannonType::FireProjecttile;

private:
	bool IsReadyToFire();
	void Reload();
	void fireProjectile();
	void fireTrace();

private:
	bool bReadyToFire = true;
	FTimerHandle ReloadTimer;

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* CannonMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire param")
	TSubclassOf <class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire param")
	float FireRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire param")
	float FireRange = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire param")
	float Damage = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire param")
	float shells = 50.0f;
};
