// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manipulable_Object.h"
#include "Energy_Restorer.generated.h"

/**
 * 
 */
UCLASS()
class BOOK_PROJECT_API AEnergy_Restorer : public AManipulable_Object
{
	GENERATED_BODY()
	
	public:
		AEnergy_Restorer();
		AEnergy_Restorer(const FObjectInitializer &ObjectInitializer);
		~AEnergy_Restorer();
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Energy Restoration Properties")
			class UParticleSystemComponent* restorationParticle;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Energy Restoration Properties")
			class USphereComponent* sphereCollider;
	protected:
		virtual void BeginPlay() override;
		float originalAmountOfEnergy;
		class AAvatar* player;
	public:
		virtual void interActionCommand() override;
		virtual void Move() override;
		UFUNCTION()
			void Collision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		UFUNCTION()
			void EndCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
