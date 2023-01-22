// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>
		(TEXT("RootComponent"));
	RootComponent = SceneComp;

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	CannonMesh->SetupAttachment(SceneComp);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ProjectileSpawnPoint->SetupAttachment(CannonMesh);
}

void ACannon::Fire()
{
	if (shells < 1)
	{
		return;
	}

	if (countShells < 1)
	{
		countShells = 5;
		--shells;
		return;
	}

	if (CannonType == ECannonType::FireProjecttile)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Purple, "Fire projectile");
		--countShells;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Fire trace");
		--countShells;
	}

	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, 
		&ACannon::Fire, FireRate, false);

}

void ACannon::FireSpecial()
{
	if (!IsReadyToFire())
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Green, "Fire special");

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


