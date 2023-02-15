#include "TankFactory.h"
#include "Kismet/GameplayStatics.h"

ATankFactory::ATankFactory()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>
		(TEXT("RootComponent"));
	RootComponent = SceneComp;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>
		(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>
		(TEXT("BuildingMesh"));
	BuildingMesh->SetupAttachment(BoxCollision);

	UStaticMesh* buildingMeshTemp = LoadObject<UStaticMesh>(this, *BuildingMeshPath);
	if (buildingMeshTemp)
		BuildingMesh->SetStaticMesh(buildingMeshTemp);

	TankSpawnPoint = CreateDefaultSubobject<UArrowComponent>
		(TEXT("TankSpawnPoint"));
	TankSpawnPoint->SetupAttachment(BuildingMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>
		(TEXT("HealthComponent"));
	HealthComponent->OnHealthChanged.AddUObject(this,
		&ATankFactory::DamageTaked);
	HealthComponent->OnDie.AddUObject(this, &ATankFactory::Die);

}

void ATankFactory::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
}

void ATankFactory::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle spawnTimer;
	GetWorld()->GetTimerManager().SetTimer(spawnTimer, this,
		&ATankFactory::SpawnNewTank, SpawnTankRate, true, SpawnTankRate);
}

void ATankFactory::SpawnNewTank()
{
	if (idxTankCount < tankCount)
	{
		FTransform spawnTransform(TankSpawnPoint->GetComponentRotation(),
			TankSpawnPoint->GetComponentLocation(), FVector(1));
		ATankPawn* newTank = GetWorld()->SpawnActorDeferred<ATankPawn>(SpawnTankClass,
			spawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		//
		newTank->SetPatrollingPoints(TankWayPoints);
		//
		UGameplayStatics::FinishSpawningActor(newTank, spawnTransform);
		++idxTankCount;
	}
}

void ATankFactory::Die()
{
	if (ptrMapLoader)
	{
		ptrMapLoader->SetIsActivated(true);
	}
		
	UStaticMesh* buildingMeshTemp = LoadObject<UStaticMesh>(this, *DestroyMeshPath);
	if (buildingMeshTemp)
		BuildingMesh->SetStaticMesh(buildingMeshTemp);
}

void ATankFactory::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Tank factory damage: %f, health: %f"),
		DamageValue, HealthComponent);
}

