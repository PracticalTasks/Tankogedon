#include "ShootingMachines.h"

void AShootingMachines::BeginPlay()
{
	Super::BeginPlay();
	SetupCannon(EquippedCannonClass);
}

AShootingMachines::AShootingMachines()
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

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnHealthChanged.AddUObject(this, &AShootingMachines::DamageTake);
	HealthComponent->OnDie.AddUObject(this, &AShootingMachines::Die);
}

void AShootingMachines::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
}

void AShootingMachines::DamageTake(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), HealthComponent->GetHealth());
}

ACannon* AShootingMachines::GetCannon() const
{
	return Cannon;
}

void AShootingMachines::Die()
{
	if (Cannon)
	{
		Cannon->Destroy();
	}

	Destroy();
}

void AShootingMachines::SetupCannon(TSubclassOf<ACannon> newCannonClass)
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

void AShootingMachines::Fire()
{
	if (Cannon)
	{
		Cannon->Fire();
	}
}

void AShootingMachines::FireSpecial()
{
	if (Cannon)
	{
		Cannon->FireSpecial();
	}
}
