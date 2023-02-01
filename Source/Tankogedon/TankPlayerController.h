#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Cannon.h"
#include "TankPlayerController.generated.h"

UCLASS()
class TANKOGEDON_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY()
	class ATankPawn* TankPawn;
	
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
	FVector GetMousePosition() { return MousePos; };

protected:
	virtual void BeginPlay() override;

	void GetForwardValue(float Value);
	void GetRightValue(float Value);
	void GetRotateRightValue(float Value);

	void Fire();
	void FireSpecial();
	void swapCannon();
	void ChangeAmmo();

	FVector MousePos;
};
