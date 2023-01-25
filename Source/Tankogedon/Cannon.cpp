// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Projectile.h"
#include "Components/SceneComponent.h"
#include "DrawDebugHelpers.h"
#include "Logging/LogMacros.h"
#include <winuser.h>

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

	}
	else if(CannonType == ECannonType::FireAltProjecttile)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, "Fire alter projectile");
		AuxiliaryFireFunct();
	}
	else
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
			DrawDebugLine(GetWorld(), Start, hitResult.Location,
				FColor::Red, false, 0.2f, 0, 5);
			if (hitResult.GetActor())
			{
				AActor* OverlappedActor = hitResult.GetActor();
				UE_LOG(LogTemp, Warning, TEXT("Overlapped actor: %s"),
					*OverlappedActor->GetName());
				OverlappedActor->Destroy();
			}
		}
		else
		{
			DrawDebugLine(GetWorld(), Start, End,
				FColor::Yellow, false, 0.2f, 0, 5);
		}

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

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();

	bReadyToFire = true;
	
}


