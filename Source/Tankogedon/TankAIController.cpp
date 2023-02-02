#include "TankAIController.h"
#include "DrawDebugHelpers.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TankPawn->GetForwardValue(1.0f);
	//UE_LOG(LogTemp, Warning, TEXT("AI Rotation forwardAngle: %f rightAngle: %frotationValue:% f"), forwardAngle, rightAngle, rotationValue);
    TankPawn->GetRotationRightValue(GetRotationValue());

	Targeting();
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	TankPawn = Cast<ATankPawn>(GetPawn());
	if (TankPawn)
	{
		PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		FVector pawnLocation = TankPawn->GetActorLocation();
		MovementAccurency = TankPawn->GetMovementAccurency();
		TArray<FVector> points = TankPawn->GetPatrollingPoints();
		for (FVector point : points)
		{
			PatrollingPoints.Add(point + pawnLocation);
		}
		CurrentPatrolPointIndex = 0;
	}
}

float ATankAIController::GetRotationValue()
{
	FVector currentPoint = PatrollingPoints[CurrentPatrolPointIndex];
	FVector pawnLocation = TankPawn->GetActorLocation();
	if (FVector::Distance(currentPoint, pawnLocation) <= MovementAccurency)
	{
		CurrentPatrolPointIndex++;
		if (CurrentPatrolPointIndex >= PatrollingPoints.Num())
			CurrentPatrolPointIndex = 0;
	}

	FVector moveDirection = currentPoint - pawnLocation;
	moveDirection.Normalize();
	FVector forwardDirection = TankPawn->GetActorForwardVector();
	FVector rightDirection = TankPawn->GetActorRightVector();

	float forwardAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(forwardDirection, moveDirection)));
	float rightAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(rightDirection, moveDirection)));
	float rotationValue = 0;
	if (forwardAngle > 5)
		rotationValue = 1;
	if (rightAngle > 90)
		rotationValue = -rotationValue;

	return rotationValue;
}

void ATankAIController::Targeting()
{
	if (CanFire())
		Fire();
	else
		RotateToPlayer();
}

void ATankAIController::RotateToPlayer()
{
	if (IsPlayerInRange())
		TankPawn->RotateTurretTo(PlayerPawn->GetActorLocation());
}

bool ATankAIController::IsPlayerInRange()
{
	if (PlayerPawn)
	{
		return FVector::Distance(TankPawn->GetActorLocation(),
			PlayerPawn->GetActorLocation()) <= TargetingRange;
	}

	return false;
}

bool ATankAIController::CanFire()
{
	if (!IsPlayerSeen())
	{
		return false;
	}
	FVector targetingDir = TankPawn->GetTurretForwardVector();
	FVector dirToPlayer = PlayerPawn->GetActorLocation() -
		TankPawn->GetActorLocation();
	dirToPlayer.Normalize();
	float aimAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct
	(targetingDir, dirToPlayer)));

	return aimAngle <= Accurency;
}

void ATankAIController::Fire()
{
	TankPawn->Fire();

}

bool ATankAIController::IsPlayerSeen()
{
	FVector playerPos = PlayerPawn->GetActorLocation();
	FVector eyesPos = TankPawn->GetEyesPosition();
	FHitResult hitResult;
	FCollisionQueryParams traceParams =
		FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
	traceParams.bTraceComplex = true;
	traceParams.AddIgnoredActor(TankPawn);
	traceParams.bReturnPhysicalMaterial = false;

	if (GetWorld()->LineTraceSingleByChannel(hitResult, eyesPos, playerPos,
		ECollisionChannel::ECC_Visibility, traceParams))
	{

		if (hitResult.GetActor())
		{
			DrawDebugLine(GetWorld(), eyesPos, hitResult.Location,
				FColor::Green, false, 0.5f, 0, 10.0f);
			return hitResult.GetActor() == PlayerPawn;
		}
	}
	DrawDebugLine(GetWorld(), eyesPos, playerPos, FColor::Red, false, 0.5f, 0, 10.0f);
	return false;

}
