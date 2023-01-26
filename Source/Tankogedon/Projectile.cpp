// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceneComp;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(RootComponent);
	//ProjectileMesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnMeshOverlapBegin);
	//ProjectileMesh->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("BoxCollision"));
	SphereCollision->SetupAttachment(ProjectileMesh);
	SphereCollision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnMeshOverlapBegin);
}

void AProjectile::Start()
{
	GetWorld()->GetTimerManager().SetTimer(MovementTimer, this, &AProjectile::Move,
		MoveRate, true, 0.0f); 
}

void AProjectile::Move()
{
	FVector nextPosition = GetActorLocation() + GetActorForwardVector() *
		MoveSpeed * MoveRate;
	SetActorLocation(nextPosition);
}

void AProjectile::OnMeshOverlapBegin(class UPrimitiveComponent*
	OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* 
	OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlapped actor: %s"),
			*OtherActor->GetName());
		OtherActor->Destroy();
		Destroy();
	}


}

