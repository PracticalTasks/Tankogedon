#include "TankPlayerController.h"
#include "TankPawn.h"

void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this,
		&ATankPlayerController::GetForwardValue);

	InputComponent->BindAxis("MoveRight", this,
		&ATankPlayerController::GetRightValue);

}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
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
