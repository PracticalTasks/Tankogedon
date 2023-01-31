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

private: 
	float targetForwardAxisValue = 0.0f;
	float targetRightAxisValue = 0.0f;
	float targetRotationRightAxisValue = 0.0f;

	void MoveForward(float DeltaTime);
	void MoveRight(float DeltaTime);
	void MoveRotationRight(float DeltaTime);
	void TurretRotation(float DeltaTime);
	
};
