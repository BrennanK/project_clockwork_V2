// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manipulable_Object.h"
#include "Fire_Trap.generated.h"

/**
 * 
 */
UCLASS()
class BOOK_PROJECT_API AFire_Trap : public AManipulable_Object
{
	GENERATED_BODY()
	
	public:
		AFire_Trap();
		AFire_Trap(const FObjectInitializer &ObjectInitializer);

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components of Trap")
			class UBoxComponent* fireBox;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components of Trap")
			class UParticleSystemComponent* fireParticle;

		UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Components of Trap")
			class UParticleSystemComponent* waterParticle;

		UPROPERTY(EditAnywhere, Category = "Damage To Player")
			float damageToPlayer;
		
		UPROPERTY(EditAnywhere,Category = "Start On?")
			bool activateOnPlay;

		UPROPERTY(EditAnywhere, Category = "Delay For Water")
			float delayToTurnWaterOn;

		UPROPERTY(EditAnywhere, Category = "Delay For Water")
			float delayToTurnWaterOff;

		UPROPERTY(EditAnywhere, Category = "Delay For Water")
			float delayToTurnFireOff;

		FTimerHandle fireOffHandle;

		FTimerHandle turnOffHandle;
	protected:
		virtual void BeginPlay() override;

	public:
		UFUNCTION()
			void Collision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		virtual void interActionCommand()override;

		void douseFire();

		void deactivateFire();

		void turnOffWater();

		UFUNCTION(BlueprintImplementableEvent)
			void turnOnFireSound();

		UFUNCTION(BlueprintImplementableEvent)
			void turnOffFireSound();

		UFUNCTION(BlueprintImplementableEvent)
			void playWaterSoundEffect(int indexOfSound);
};
