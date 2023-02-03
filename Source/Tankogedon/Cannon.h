#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStruct.h"
#include "Components/ArrowComponent.h"
#include "Particles\ParticleSystemComponent.h"
#include "Components\AudioComponent.h"
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
	void fireProjectile();
	void fireTrace();

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
	float FireRate = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire param")
	float FireRange = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire param")
	float Damage = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire param")
	int32 shells = 50;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Effects")
	class UParticleSystemComponent* ShootEffect;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Effects")
	class UAudioComponent* AudioEffect;

};
