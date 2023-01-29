#include "HealthComponent.h"

void UHealthComponent::TakeDamage(FDamageData DamageData)
{
	float takedDamageValue = DamageData.DamageValue;
	CurrentHealth -= takedDamageValue;
	if (CurrentHealth <= 0)
	{
		if (OnDie.IsBound())
			OnDie.Broadcast();
	}
	else
	{
		if (OnHealthChanged.IsBound())
			OnHealthChanged.Broadcast(takedDamageValue);
	}

}

float UHealthComponent::GetHealth() const
{
	return CurrentHealth;
}

float UHealthComponent::GeyHealthState() const
{
	return CurrentHealth / MaxHealth;
}

void UHealthComponent::AddHealth(float newHealth)
{
	CurrentHealth += MaxHealth;
	if (CurrentHealth > MaxHealth)
		CurrentHealth = MaxHealth;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

