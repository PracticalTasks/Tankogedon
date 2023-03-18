#include "PhysicsProjectile.h"
#include "Kismet/KismetMathLibrary.h"
#include "DamageTaker.h"

APhysicsProjectile::APhysicsProjectile()
{
	PhysicsComponent = CreateDefaultSubobject<UPhysicsComponent>(TEXT
	("PhysicsComponent"));
	TrailEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT
	("Trail effect"));	
	TrailEffect->SetupAttachment(RootComponent);
}

void APhysicsProjectile::Start()
{
	MoveVector = GetActorForwardVector() * TrajectorySimulationSpeed;
	CurrentTrajectory = PhysicsComponent->GenerateTrajectory(GetActorLocation(),
		MoveVector, TrajectorySimulationMaxTime, TrajectorySimulationTimeStep, 0);
	if (ShowTrajectory)
	{
		for (FVector position : CurrentTrajectory)
		{
			DrawDebugSphere(GetWorld(), position, 5, 8, 
				 FColor::Red, true, 1, 0, 2);
		}
	}
	TrajectoryPointIndex = 0;
	TrailEffect->ActivateSystem();
	Super::Start();
}

void APhysicsProjectile::Move()
{
	FVector currentMoveVector = CurrentTrajectory[TrajectoryPointIndex] -
		GetActorLocation();
	currentMoveVector.Normalize();
	FVector newLocation = GetActorLocation() + currentMoveVector * MoveSpeed *
		MoveRate;
	SetActorLocation(newLocation);
	if (FVector::Distance(newLocation, CurrentTrajectory[TrajectoryPointIndex]) <=
		MoveAccurency)
	{
		TrajectoryPointIndex++;
		if (TrajectoryPointIndex >= CurrentTrajectory.Num())
		{
			if(explode)
				Explode();
			Destroy();
		}
		else
		{
			FRotator newRotation = UKismetMathLibrary::FindLookAtRotation
				(GetActorLocation(), CurrentTrajectory[TrajectoryPointIndex]);
			SetActorRotation(newRotation);
		}

	}
}


void APhysicsProjectile::OnMeshOverlapBegin(class UPrimitiveComponent*
	OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent*
	OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Explode();
	Destroy();
}
