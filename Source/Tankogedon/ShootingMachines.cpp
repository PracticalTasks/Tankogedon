#include "ShootingMachines.h"

void ShootingMachines::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
}

void ShootingMachines::DamageTake(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), HealthComponent->GetHealth());
}

void ShootingMachines::Fire()
{
	if (Cannon)
	{
		Cannon->Fire();
	}
}
