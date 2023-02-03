// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Projectile.h"
#include "Components/SceneComponent.h"
#include "DrawDebugHelpers.h"
#include "Logging/LogMacros.h"
#include "DamageTaker.h"
#include "GameStruct.h"

ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>
		(TEXT("RootComponent"));
	RootComponent = SceneComp;

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	CannonMesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ProjectileSpawnPoint->SetupAttachment(CannonMesh);
}

void ACannon::AuxiliaryFireFunct()
{
	--shells;
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>
		(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(),
			ProjectileSpawnPoint->GetComponentRotation());
	if (Projectile)
	{
		Projectile->Start();
	}
}

void ACannon::FireTrace()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Fire trace");
	--shells;
	FHitResult hitResult;
	FCollisionQueryParams traceParams = FCollisionQueryParams();
	traceParams.AddIgnoredActor(this);
	traceParams.bReturnPhysicalMaterial = false;
	FVector Start = ProjectileSpawnPoint->GetComponentLocation();
	FVector End = Start + ProjectileSpawnPoint->GetForwardVector() * FireRange;

	if (GetWorld()->LineTraceSingleByChannel(hitResult, Start, End,
		ECollisionChannel::ECC_Visibility, traceParams))
	{
		if (hitResult.GetActor())
		{
			DrawDebugLine(GetWorld(), Start, hitResult.Location,
				FColor::Red, false, 0.2f, 0, 5);
			IDamageTaker* damageActor = Cast<IDamageTaker>(hitResult.GetActor());
			if (damageActor)
			{
				FDamageData damageData;
				damageData.DamageMaker = this;
				damageData.DamageValue = Damage;
				damageData.Instigator = GetOwner();

				damageActor->TakeDamage(damageData);
			}
			//UE_LOG(LogTemp, Warning, TEXT("Overlapped actor: %s"),
			//	*OverlappedActor->GetName());
			//OverlappedActor->Destroy();
		}
	}
	else
	{
		DrawDebugLine(GetWorld(), Start, End,
			FColor::Yellow, false, 0.2f, 0, 5);
	}
}

void ACannon::AddAmmo(int CountShells)
{
	shells += CountShells;
}

void ACannon::Fire()
{
	if (!IsReadyToFire() || shells < 1)
	{
		return;
	}
	if (CannonType == ECannonType::FireProjecttile)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, "Fire projectile");
		AuxiliaryFireFunct();
		UE_LOG(LogTemp, Display, TEXT("Ammo Fire projectile: %i"), shells);

	}
	else if(CannonType == ECannonType::FireAltProjecttile)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, "Fire alter projectile");
		AuxiliaryFireFunct();
		UE_LOG(LogTemp, Display, TEXT("Ammo Fire alter projectile: %i"), shells);
	}
	else
	{
		FireTrace();
	}

	bReadyToFire = false;

	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, 
		&ACannon::Reload, FireRate, false);
}

void ACannon::FireSpecial()
{
	if (!IsReadyToFire())
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "Fire special");

	bReadyToFire = false;

	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this,
		&ACannon::Reload, FireRate, false);
}

bool ACannon::IsReadyToFire()
{
	return bReadyToFire;
}

void ACannon::Reload()
{
	bReadyToFire = true;
}

void ACannon::BeginPlay()
{
	Super::BeginPlay();

	bReadyToFire = true;
}

void ACannon::OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AActor* owner = GetOwner();
	AActor* OwnerByOwner = Owner != nullptr ? GetOwner() : nullptr;

	if (OtherActor != Owner || OtherActor != OwnerByOwner)
	{
		IDamageTaker* DamageActor = Cast<IDamageTaker>(OtherActor);

		if (DamageActor)
		{
			FDamageData damageData;
			damageData.DamageValue = Damage;
			damageData.Instigator = Owner;
			damageData.DamageMaker = this;

			DamageActor->TakeDamage(damageData);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Overlapped actor: %s"),
				*OtherActor->GetName());
			OtherActor->Destroy();
		}
	}
}

