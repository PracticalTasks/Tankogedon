#include "MapLoader.h"
#include "Kismet/GameplayStatics.h"

AMapLoader::AMapLoader()
{
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>
		(TEXT("RootComponent"));
	RootComponent = SceneComp;

	MapLoaderMesh = CreateDefaultSubobject<UStaticMeshComponent>
		(TEXT("MapLoaderMesh"));
	MapLoaderMesh->SetupAttachment(SceneComp);

	ActivatedLight = CreateDefaultSubobject<UPointLightComponent>
		(TEXT("ActivatedLights"));
	ActivatedLight->SetupAttachment(RootComponent);

	DeactivatedLight = CreateDefaultSubobject<UPointLightComponent>
		(TEXT("DeactivatedLights"));
	DeactivatedLight->SetupAttachment(RootComponent);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT
	("BoxCollision"));
	BoxCollision->SetupAttachment(SceneComp);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this,
		&AMapLoader::OnMeshOverlapBegin);


	SetActiveLights();
}

void AMapLoader::SetIsActivated(bool NewIsActivated)
{
	IsActivated = NewIsActivated;

	SetActiveLights();
}

void AMapLoader::BeginPlay()
{
	Super::BeginPlay();
	SetActiveLights();
}

void AMapLoader::SetActiveLights()
{
	ActivatedLight->SetHiddenInGame(!IsActivated);
	DeactivatedLight->SetHiddenInGame(IsActivated);
}

void AMapLoader::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp,int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsActivated)
		return;

	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (OtherActor == PlayerPawn)
		UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}

