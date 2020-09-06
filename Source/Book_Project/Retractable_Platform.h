// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manipulable_Object.h"
#include "Retractable_Platform.generated.h"

/**
 * 
 */
UCLASS()
class BOOK_PROJECT_API ARetractable_Platform : public AManipulable_Object
{
	GENERATED_BODY()
	
	public:
		ARetractable_Platform();
		ARetractable_Platform(const FObjectInitializer &ObjectInitializer);
		~ARetractable_Platform();
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh of The Moving Platform")
			class UStaticMeshComponent* movingMesh;

		UPROPERTY(EditAnywhere, Category = "Locations of Extension and Retraction")
			FVector locationWhenRetracted;

		UPROPERTY(EditAnywhere, Category = "Locations of Extension and Retraction")
			FVector LocationWhenExtended;

		UPROPERTY(EditAnywhere, Category = "Direction and Speed")
			float direction;

		UPROPERTY(EditAnywhere, Category = "Direction and Speed")
			float initialDelay;

		UPROPERTY(EditAnywhere, Category = "Is this tied to a Panel?")
			bool autoActivate;

		UPROPERTY(EditAnywhere, Category = "Should the Direction Change")
			bool shouldChange;

		UPROPERTY(EditAnywhere, Category = "Delay until Next movement")
			float movementDelay;
		
		FTimerHandle resetCycle;
	protected:
		virtual void BeginPlay() override;

	public:

		virtual void interActionCommand() override;

		void doWeChangeDirections();

		virtual void Move() override;

		UFUNCTION(BlueprintImplementableEvent)
			void activatePlatformMovementSound(int indexForSoundCue);

};
