#include "Projectile.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "DamageTaker.h"
#include <Components/SceneComponent.h>
#include <Components/PrimitiveComponent.h>

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceneComp;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnMeshOverlapBegin);
	ProjectileMesh->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);

	//SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("BoxCollision"));
	//SphereCollision->SetupAttachment(ProjectileMesh);
	//SphereCollision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	//SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnMeshOverlapBegin);
}

void AProjectile::Start()
{
	GetWorld()->GetTimerManager().SetTimer(MovementTimer, this, &AProjectile::Move,
		MoveRate, true, 0.0f); 

	//Вызывает метод уничтожения снаряда по времени
	GetWorld()->GetTimerManager().SetTimer(DestroyTimer, this, &AProjectile::destroyByTime,
		timeToDestroy, true, timeToDestroy);
}

void AProjectile::Move()
{
	FVector nextPosition = GetActorLocation() + GetActorForwardVector() *
		MoveSpeed * MoveRate;
	SetActorLocation(nextPosition);
}

void AProjectile::destroyByTime()
{
	Destroy();
}

void AProjectile::OnMeshOverlapBegin(class UPrimitiveComponent*
	OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* 
	OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
			//UE_LOG(LogTemp, Warning, TEXT("Overlapped actor: %s"),
			//	*OtherActor->GetName());
			//OtherActor->Destroy();
			
			UPrimitiveComponent* mesh =
				Cast<UPrimitiveComponent>(OtherActor->GetRootComponent());
			if (mesh)
			{
				if (mesh->IsSimulatingPhysics())
				{
					for (int32 i{}; i < idxForce; ++i)
					{
						FVector forceVector =
							OtherActor->GetActorLocation() - GetActorLocation();
						forceVector.Normalize();
						mesh->AddForce(forceVector * PushForce, NAME_None, true);
					}
				}
				else
				{
					OtherActor->Destroy();
				}
			}

		}

		Destroy();
	}


}

