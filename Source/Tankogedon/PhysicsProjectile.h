#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "PhysicsComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsProjectile.generated.h"

UCLASS()
class TANKOGEDON_API APhysicsProjectile : public AProjectile
{
	GENERATED_BODY()

public:
	APhysicsProjectile();

	virtual void Start() override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UPhysicsComponent* PhysicsComponent;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UParticleSystemComponent* TrailEffect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float MoveAccurency = 10.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category =
		"Movement|Trajectory")
	float TrajectorySimulationMaxTime = 30.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category =
		"Movement|Trajectory")
	float TrajectorySimulationTimeStep = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category =
		"Movement|Trajectory")
	float TrajectorySimulationSpeed = 20.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category =
		"Movement|Trajectory")
	bool ShowTrajectory = false;
	UPROPERTY(BlueprintReadWrite, Category = "Movement params")
	FVector MoveVector;
	UPROPERTY(BlueprintReadWrite, Category = "Movement params")
	TArray<FVector> CurrentTrajectory;
	UPROPERTY(BlueprintReadWrite, Category = "Movement params")
	int32 TrajectoryPointIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Explode")
	bool explode = true;

protected:
	virtual void Move() override;


	
};
