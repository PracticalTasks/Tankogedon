#pragma once

#include "CoreMinimal.h"
#include "DamageTaker.h"
#include "HealthComponent.h"
#include "GameStruct.h"
#include "Cannon.h"

class TANKOGEDON_API ShootingMachines : public IDamageTaker
{
public:
	//ShootingMachines();

	UFUNCTION()
	void TakeDamage(FDamageData DamageData) override;
	UFUNCTION()
	void DamageTake(float Value);

	virtual void Die() = 0;
	virtual void SetupCannon(TSubclassOf<ACannon> newCannonClass) = 0;
	void Fire();
	void SetHealthComponent(UHealthComponent* _HealthComponent) { HealthComponent = _HealthComponent; };
	
	//ShootingMachines* getPtr() { return this; };

public:
	UPROPERTY()
	ACannon* Cannon;
	UHealthComponent* HealthComponent;
	//UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	//UStaticMeshComponent* BodyMesh;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components");
	//UStaticMeshComponent* TurretMesh;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components");
	//class UHealthComponent* HealthComponent;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon");
	//class UArrowComponent* CannonSetupPoint;

};
