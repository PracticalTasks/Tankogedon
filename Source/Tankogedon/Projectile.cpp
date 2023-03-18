#include "Projectile.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
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
			damageData.DamageValue = damage;
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

void AProjectile::Explode()
{
	FVector startPos = GetActorLocation();
	FVector endPos = startPos + FVector(0.1f);
	FCollisionShape Shape = FCollisionShape::MakeSphere(ExplodeRadius);
	FCollisionQueryParams params = FCollisionQueryParams::DefaultQueryParam;
	params.AddIgnoredActor(this);
	params.bTraceComplex = true;
	params.TraceTag = "Explode Trace";
	TArray<FHitResult> AttackHit;
	FQuat Rotation = FQuat::Identity;
	bool sweepResult = GetWorld()->SweepMultiByChannel(AttackHit, startPos,
		endPos, Rotation, ECollisionChannel::ECC_Visibility, Shape, params);
	GetWorld()->DebugDrawTraceTag = "Explode Trace";
	if (sweepResult)
	{
		for (FHitResult hitResult : AttackHit)
		{
			AActor* otherActor = hitResult.GetActor();
			if (!otherActor)
				continue;
			IDamageTaker* damageTakerActor = Cast<IDamageTaker>(otherActor);
			Damage(damageTakerActor, otherActor);
		}
	}
}

void AProjectile::Damage(IDamageTaker* damageTakerActor, AActor* otherActor)
{
	if (damageTakerActor)
	{
		FDamageData damageData;
		damageData.DamageValue = damage;
		damageData.Instigator = GetOwner();
		damageData.DamageMaker = this;
		damageTakerActor->TakeDamage(damageData);
	}
	else
	{
		UPrimitiveComponent* mesh =
			Cast<UPrimitiveComponent>(otherActor->GetRootComponent());
		if (mesh)
		{
			if (mesh->IsSimulatingPhysics())
			{
				for (int32 i{}; i < idxForce; ++i)
				{
					FVector forceVector =
						otherActor->GetActorLocation() - GetActorLocation();
					forceVector.Normalize();
					mesh->AddForce(forceVector * PushForce, NAME_None, true);
				}
			}
		}
	}
}

