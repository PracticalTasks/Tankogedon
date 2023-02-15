#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankPawn.h"
#include "TankAIController.generated.h"

UCLASS()
class TANKOGEDON_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY()
	class ATankPawn* TankPawn;
	UPROPERTY()
	APawn* PlayerPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Patrolpoints",
	Meta = (MakeEditWidget = true))
	TArray<FVector> PatrollingPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Accurency")
	float MovementAccurency;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float TargetingRange = 5000;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float TargetingSpeed = 1.0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float Accurency = 20;

	int32 CurrentPatrolPointIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	float changeWeaponRate = 5.0f;
	FTimerHandle timerChangeWeapon;
protected:
	virtual void BeginPlay() override;

	float GetRotationValue();
	void Targeting();
	void RotateToPlayer();
	bool IsPlayerInRange();
	bool CanFire();
	void Fire();
	void Initialize();

	bool IsPlayerSeen();
	void changeWeapon();

};
