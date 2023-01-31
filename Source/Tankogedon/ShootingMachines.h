#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DamageTaker.h"
#include "HealthComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Cannon.h"
#include "ShootingMachines.generated.h"


class UStaticMeshComponent;
class ACannon;
UCLASS()
class TANKOGEDON_API AShootingMachines : public APawn, public IDamageTaker
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components");
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components");
	class UBoxComponent* BoxCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components");
	class UHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon");
	class UArrowComponent* CannonSetupPoint;
public:
	UPROPERTY()
	ACannon* Cannon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon");
	TSubclassOf<ACannon> EquippedCannonClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon");
	TSubclassOf<ACannon> SecondCannonClass;

public:
	AShootingMachines();

	UFUNCTION()
	void TakeDamage(FDamageData DamageData) override;
	UFUNCTION()
	void DamageTake(float Value);
	ACannon* GetCannon() const;
	//void SetupCannon(TSubclassOf<ACannon> newCannonClass) override;

	virtual void Die();
	virtual void SetupCannon(TSubclassOf<ACannon> newCannonClass);
	void Fire();
	void FireSpecial();
};
