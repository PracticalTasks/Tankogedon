#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"

class UStaticMeshComponent;
class ACannon;

UCLASS()

class TANKOGEDON_API ATankPawn : public APawn
{
	GENERATED_BODY()

public:
	ATankPawn();

	virtual void Tick(float DeltaTime) override;
	void GetForwardValue(float Value);
	void GetRightValue(float Value);
	void GetRotationRightValue(float Value);

	void Fire();
	void FireSpecial();
	void SetupCannon(TSubclassOf<ACannon> newCannonClass);
	void changeWeapon();

public:
	UPROPERTY();
	ACannon* Cannon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon");
	TSubclassOf<ACannon> EquippedCannonClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon");
	TSubclassOf<ACannon> SecondCannonClass;

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components");
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components");
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components");
	class UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components");
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components");
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon");
	class UArrowComponent* CannonSetupPoint;

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
