#include "Turret.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/KismetMathLibrary.h"

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Targeting();
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	FTimerHandle targetingTimer;
	GetWorld()->GetTimerManager().SetTimer(targetingTimer, this,
		&ATurret::Targeting, TargetingRate, true, TargetingRate);

	GetWorld()->GetTimerManager().SetTimer(timerChangeWeapon, this,
		&ATurret::changeWeapon, changeWeaponRate, true);
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

	if (!IsPlayerSeen() || !IsPlayerInRange())
	{
		return;
	}


	RotateToPlayer();

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

FVector ATurret::GetEyesPosition() const
{
	return CannonSetupPoint->GetComponentLocation();
}

void ATurret::changeWeapon()
{
	TSubclassOf<ACannon> tmpCannon = EquippedCannonClass;
	EquippedCannonClass = SecondCannonClass;
	SecondCannonClass = tmpCannon;
	SetupCannon(EquippedCannonClass);
}

void ATurret::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UStaticMesh* bodyMeshTemp = LoadObject<UStaticMesh>(this, *BuildingMeshPath);
	if (bodyMeshTemp)
		BodyMesh->SetStaticMesh(bodyMeshTemp);

	UStaticMesh* turretMeshTemp = LoadObject<UStaticMesh>(this, *TurretMeshPath);
	if (turretMeshTemp)
		TurretMesh->SetStaticMesh(turretMeshTemp);

}

bool ATurret::IsPlayerSeen()
{
	FVector playerPos = PlayerPawn->GetActorLocation();
	FVector eyesPos = GetEyesPosition();
	FHitResult hitResult;
	FCollisionQueryParams traceParams =
		FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
	traceParams.bTraceComplex = true;
	traceParams.AddIgnoredActor(this);
	traceParams.bReturnPhysicalMaterial = false;

	if (GetWorld()->LineTraceSingleByChannel(hitResult, eyesPos, playerPos,
		ECollisionChannel::ECC_Visibility, traceParams))
	{

		if (hitResult.GetActor())
		{
			if (hitResult.GetActor() == PlayerPawn)
			{
				DrawDebugLine(GetWorld(), eyesPos, hitResult.Location,
					FColor::Green, false, 0.5f, 0, 10.0f);
			}
			DrawDebugLine(GetWorld(), eyesPos, hitResult.Location,
				FColor::Black, false, 0.5f, 0, 10.0f);
			return hitResult.GetActor() == PlayerPawn;
		}
	}
	DrawDebugLine(GetWorld(), eyesPos, playerPos, FColor::Red, false, 0.5f, 0, 10.0f);
	return false;
}

