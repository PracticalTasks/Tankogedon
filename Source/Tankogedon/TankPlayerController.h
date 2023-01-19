#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

UCLASS()
class TANKOGEDON_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY()
	class ATankPawn* TankPawn;
	
	virtual void SetupInputComponent() override;

protected:
	virtual void BeginPlay() override;

	void MoveRight(float Value);
};
