#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"
#include "MapLoader.generated.h"

class UPointLightComponent;

UCLASS()
class TANKOGEDON_API AMapLoader : public AActor
{
	GENERATED_BODY()
	
public:	
	AMapLoader();
	void SetIsActivated(bool NewIsActivated);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component");
	class UStaticMeshComponent* MapLoaderMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component");
	class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UPointLightComponent* ActivatedLight;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UPointLightComponent* DeactivatedLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component");
	FName LevelName = "SecondLevel";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level loading params")
	bool IsActivated = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SetActiveLights();

	UFUNCTION()
	void OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor*
		OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

};
