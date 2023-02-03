#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/Pawn.h"
#include "DamageTaker.h"
#include "HealthComponent.h"
#include "ShootingMachines.h"
#include "TankPawn.generated.h"

class UStaticMeshComponent;
class ACannon;

UCLASS()

class TANKOGEDON_API ATankPawn : public AShootingMachines
{
	GENERATED_BODY()

public:
	ATankPawn();

	void Tick(float DeltaTime) override;
	void GetForwardValue(float Value);
	void GetRightValue(float Value);
	void GetRotationRightValue(float Value);
	void MoveForward(float DeltaTime);
	void MoveRotationRight(float DeltaTime);
	UFUNCTION()
	TArray<FVector> GetPatrollingPoints() const { return PatrollingPoints; };
	UFUNCTION()
	float GetMovementAccurency() const { return MovementAccurency; };
	UFUNCTION()
	FVector GetTurretForwardVector() const;
	UFUNCTION()
	void RotateTurretTo(FVector TargetPosition);
	FVector GetEyesPosition() const;
	void changeWeapon();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components");
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components");
	class UCameraComponent* Camera;

	UPROPERTY();
	class ATankPlayerController* TankController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement");
	float MoveSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement");
	float RotationSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement | Rotation");
	float TurretRotationInterpolationKey = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Patrolpoints" , Meta = (MakeEditWidget = true))
	TArray<FVector> PatrollingPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Moveparams | Accurency")
	float MovementAccurency = 25;

private: 
	float targetForwardAxisValue = 0.0f;
	float targetRightAxisValue = 0.0f;
	float targetRotationRightAxisValue = 0.0f;

	void MoveRight(float DeltaTime);
	void TurretRotation(float DeltaTime);
	
};
