#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageTaker.h"
#include "TankPawn.h"
#include "Engine/TargetPoint.h" 
#include "GameStruct.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "HealthComponent.h"
#include "MapLoader.h"
#include "TankFactory.generated.h"

UCLASS()
class TANKOGEDON_API ATankFactory : public AActor, public IDamageTaker
{
	GENERATED_BODY()
	
public:	
	ATankFactory();
	UFUNCTION()
	void TakeDamage(FDamageData DamageData);

protected:
	virtual void BeginPlay() override;
	void SpawnNewTank();
	UFUNCTION()
	void Die();
	UFUNCTION()
	void DamageTaked(float DamageValue);

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* BuildingMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UArrowComponent* TankSpawnPoint;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UBoxComponent* BoxCollision;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn tanks params")
	TSubclassOf<class ATankPawn> SpawnTankClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawn tanks params")
	float SpawnTankRate = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn tanks params")
	TArray<class ATargetPoint*> TankWayPoints;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	int32 tankCount = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn tanks params")
	AMapLoader* ptrMapLoader;

	const FString BuildingMeshPath = "StaticMesh'/Engine/BasicShapes/Cube.Cube'";
	const FString DestroyMeshPath = "StaticMesh'/Engine/BasicShapes/Plane.Plane'";

	int32 idxTankCount = 0;

};
