#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "TankPlayerController.h"
#include "Kismet/KismetMathLibrary.h"

ATankPawn::ATankPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	RootComponent = BoxCollision;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(BoxCollision);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BodyMesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(BoxCollision);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveForward(DeltaTime);
	MoveRight(DeltaTime);
	MoveRotationRight(DeltaTime);
	TurretRotation(DeltaTime);
}

void ATankPawn::GetForwardValue(float Value)
{
	targetForwardAxisValue = Value;
}

void ATankPawn::GetRightValue(float Value)
{
	targetRightAxisValue = Value;
}

void ATankPawn::GetRotationRightValue(float Value)
{
	targetRotationRightAxisValue = Value;
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	TankController = Cast<ATankPlayerController>(GetController());
}

void ATankPawn::MoveForward(float DeltaTime)
{
	FVector CurrentPosition = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector movePosition = CurrentPosition + ForwardVector *
		MoveSpeed * targetForwardAxisValue * DeltaTime;
	SetActorLocation(movePosition, true);
}

void ATankPawn::MoveRight(float DeltaTime)
{
	FVector CurrentPosition = GetActorLocation();
	FVector RightVector = GetActorRightVector();
	FVector movePosition = CurrentPosition + RightVector *
		MoveSpeed * targetRightAxisValue * DeltaTime;
	SetActorLocation(movePosition, true);
}

void ATankPawn::MoveRotationRight(float DeltaTime)
{
	float yawRotation = RotationSpeed * targetRotationRightAxisValue *
		DeltaTime;
	
	float LerpRotationValue = FMath::Lerp(targetRotationRightAxisValue, 
		LerpRotationValue, TurretRotationInterpolationKey);
	FRotator currentRotation = GetActorRotation();
	yawRotation += currentRotation.Yaw;

	FRotator newRotation = FRotator(0.0f, yawRotation, 0.0f);
	SetActorRotation(newRotation);


}

void ATankPawn::TurretRotation(float DeltaTime)
{
	if (TankController)
	{
		FVector MousePos = TankController-> GetMousePosition();
		FRotator targetRotation = UKismetMathLibrary::
			FindLookAtRotation(GetActorLocation(),MousePos);
		FRotator TurretRotation = TurretMesh->GetComponentRotation();
		targetRotation.Pitch = TurretRotation.Pitch;
		targetRotation.Roll = TurretRotation.Roll;

		FRotator newTurretRotation = FMath::Lerp(TurretRotation,
			targetRotation, TurretRotationInterpolationKey);

		//UE_LOG(LogTemp, Warning, TEXT("targetRotation: %s, LerpRotation: %s"),
		//	*targetRotation.ToString(), *newTurretRotation.ToString());
		TurretMesh->SetWorldRotation(newTurretRotation);

	}
}

