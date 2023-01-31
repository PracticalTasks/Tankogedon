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
	void AddAmmo(int CountShells);
	bool IsReadyToFire();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire param")
	ECannonType CannonType = ECannonType::FireProjecttile;

private:
	void Reload();
	void AuxiliaryFireFunct();
	void FireTrace();

private:
	bool bReadyToFire = true;
	FTimerHandle ReloadTimer;

protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = "Fire param")
	int32 GetShells() { return shells; };

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
	int32 shells = 50;

	void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor*
		OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool
		bFromSweep, const FHitResult& SweepResult);
};
