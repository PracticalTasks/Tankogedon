#include "TankPlayerController.h"
#include "TankPawn.h"
#include "DrawDebugHelpers.h"

void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this,
		&ATankPlayerController::GetForwardValue);

	InputComponent->BindAxis("MoveRight", this,
		&ATankPlayerController::GetRightValue);

	InputComponent->BindAxis("RotationRight", this,
		&ATankPlayerController::GetRotateRightValue);
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	FVector MouseDirection;
	DeprojectMousePositionToWorld(MousePos, MouseDirection);
	FVector PawnPosition = TankPawn->GetActorLocation();
	MousePos.Z = PawnPosition.Z;
	FVector dir = MousePos - PawnPosition;
	dir.Normalize();
	MousePos = PawnPosition + dir * 1000;
	DrawDebugLine(GetWorld(), PawnPosition, 
		MousePos, FColor::Green, false, 0.1f, 0, 5);
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
	TankPawn = Cast<ATankPawn>(GetPawn());
}

void ATankPlayerController::GetForwardValue(float Value)
{
	if (TankPawn)
	{
		TankPawn->GetForwardValue(Value);
	}
}

void ATankPlayerController::GetRightValue(float Value)
{
	if (TankPawn)
	{
		TankPawn->GetRightValue(Value);
	}
}

void ATankPlayerController::GetRotateRightValue(float Value)
{
	if (TankPawn)
	{
		TankPawn->GetRotationRightValue(Value);
	}
}
