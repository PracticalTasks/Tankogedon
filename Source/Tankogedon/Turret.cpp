#include "Turret.h"
#include "Engine/StaticMesh.h"
#include "Kismet/KismetMathLibrary.h"

ATurret::ATurret()
{
	//PrimaryActorTick.bCanEverTick = false;
	//BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("HitCollider"));
	//RootComponent = BoxCollision;

	//BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	//BodyMesh->SetupAttachment(BoxCollision);

	//TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	//TurretMesh->SetupAttachment(BodyMesh);

	//CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("CannonSetupPoint"));
	//CannonSetupPoint->SetupAttachment(TurretMesh, "ADD_Parts_Here_Socket");

	UStaticMesh* bodyMeshTemp = LoadObject<UStaticMesh>(this, *BodyMeshPath);
	if (bodyMeshTemp)
		BodyMesh->SetStaticMesh(bodyMeshTemp);

	UStaticMesh * turretMeshTemp = LoadObject<UStaticMesh>(this, *TurretMeshPath);
	if (turretMeshTemp)
		TurretMesh->SetStaticMesh(turretMeshTemp);

	//HealthComponent = CreateDefaultSubobject<UHealthComponent>
	//	(TEXT("HealthComponent"));
	//HealthComponent->OnHealthChanged.AddUObject(this, &ATurret::DamageTake);
	//HealthComponent->OnDie.AddUObject(this, &ATurret::Die);
}

//void ATurret::TakeDamage(FDamageData DamageData)
//{
//	HealthComponent->TakeDamage(DamageData);
//}
//
//void ATurret::Die()
//{
//	Destroy();
//}
//
//void ATurret::DamageTake(float Value)
//{
//	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), HealthComponent->GetHealth());
//}

void ATurret::BeginPlay()
{
	Super::BeginPlay();
	//SetupCannon(EquippedCannonClass);
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	FTimerHandle targetingTimer;
	GetWorld()->GetTimerManager().SetTimer(targetingTimer, this,
		&ATurret::Targeting, TargetingRate, true, TargetingRate);
}

//void ATurret::SetupCannon(TSubclassOf<ACannon> newCannonClass)
//{
//	if (!newCannonClass)
//		return;
//	FActorSpawnParameters params;
//	params.Owner = this;
//	Cannon = GetWorld()->SpawnActor<ACannon>(EquippedCannonClass, params);
//	Cannon->AttachToComponent(CannonSetupPoint,
//		FAttachmentTransformRules::SnapToTargetNotIncludingScale);
//
//}

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

//void ATurret::Fire()
//{
//	if (Cannon)
//	{
//		Cannon->Fire();
//	}
//}

