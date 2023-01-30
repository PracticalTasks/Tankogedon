#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "TankPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Cannon.h"
#include "Components/ArrowComponent.h"
//#include "Logging/LogMacros.h"
#include "HealthComponent.h"
//#include <Engine/EngineTypes.h>

ATankPawn::ATankPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	RootComponent = BoxCollision;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(BoxCollision);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BodyMesh);

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>
		(TEXT("CannonSetupPoint"));
	CannonSetupPoint->AttachToComponent(TurretMesh, FAttachmentTransformRules::KeepRelativeTransform);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(BoxCollision);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	SetHealthComponent(HealthComponent);
	HealthComponent->OnHealthChanged.AddUObject(this, &ShootingMachines::DamageTake);
	HealthComponent->OnDie.AddUObject(this, &ATankPawn::Die);


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

//void ATankPawn::Fire()
//{
//	if (Cannon)
//	{
//		Cannon->Fire();
//	}
//}

void ATankPawn::FireSpecial()
{
	if (Cannon)
	{
		Cannon->FireSpecial();
	}
}

void ATankPawn::SetupCannon(TSubclassOf<ACannon> newCannonClass)
{
	if (!newCannonClass)
	{
		return;
	}
	
	if (Cannon)
	{
		Cannon->Destroy();
	}

	FActorSpawnParameters spawnParams;
	spawnParams.Instigator = this;
	spawnParams.Owner = this;

	Cannon = GetWorld()->SpawnActor<ACannon>(newCannonClass, spawnParams);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::
		SnapToTargetNotIncludingScale);
}

//void ATankPawn::TakeDamage(FDamageData DamageData)
//{
//	HealthComponent->TakeDamage(DamageData);
//}

//void ATankPawn::DamageTaked(float Value)
//{
//	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), HealthComponent->GetHealth());
//}

void ATankPawn::Die()
{
	if (Cannon)
	{
		Cannon->Destroy();
	}

	Destroy();
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	TankController = Cast<ATankPlayerController>(GetController());

	SetupCannon(EquippedCannonClass);
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
	
	//float LerpRotationValue = FMath::Lerp(targetRotationRightAxisValue, 
	//	LerpRotationValue, TurretRotationInterpolationKey);
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

