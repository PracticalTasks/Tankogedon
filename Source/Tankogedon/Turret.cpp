#include "Turret.h"
#include "Engine/StaticMesh.h"
#include "Kismet/KismetMathLibrary.h"

ATurret::ATurret()
{
	UStaticMesh* bodyMeshTemp = LoadObject<UStaticMesh>(this, *BodyMeshPath);
	if (bodyMeshTemp)
		BodyMesh->SetStaticMesh(bodyMeshTemp);

	UStaticMesh * turretMeshTemp = LoadObject<UStaticMesh>(this, *TurretMeshPath);
	if (turretMeshTemp)
		TurretMesh->SetStaticMesh(turretMeshTemp);
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	FTimerHandle targetingTimer;
	GetWorld()->GetTimerManager().SetTimer(targetingTimer, this,
		&ATurret::Targeting, TargetingRate, true, TargetingRate);
}

void ATurret::Destroyed()
{
	if (Cannon)
		Cannon->Destroy();
}

void ATurret::Targeting()
{
	if (!PlayerPawn)
		return;

	if (IsPlayerInRange())
	{
		RotateToPlayer();
	}
	if (CanFire())
	{
		Fire();
	}

}

void ATurret::RotateToPlayer()
{
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),
			PlayerPawn->GetActorLocation());
	FRotator currRotation = TurretMesh->GetComponentRotation();
	targetRotation.Pitch = currRotation.Pitch;
	targetRotation.Roll = currRotation.Roll;
	TurretMesh->SetWorldRotation(FMath::Lerp(currRotation, targetRotation,
		TargetingSpeed));
}

bool ATurret::IsPlayerInRange()
{
	return FVector::Distance(PlayerPawn->GetActorLocation(), GetActorLocation()) <=
		TargetingRange;
}

bool ATurret::CanFire()
{
	FVector targetingDir = TurretMesh->GetForwardVector();
	FVector dirToPlayer = PlayerPawn->GetActorLocation() - GetActorLocation();
	dirToPlayer.Normalize();
	float aimAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct
	(targetingDir, dirToPlayer)));
	return aimAngle <= Accurency;
}

