// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manipulable_Object.h"
#include "Trap_Door.generated.h"

/**
 * 
 */
UCLASS()
class BOOK_PROJECT_API ATrap_Door : public AManipulable_Object
{
	GENERATED_BODY()
	
	public:
		ATrap_Door();
		ATrap_Door(const FObjectInitializer &ObjectInitializer);
		~ATrap_Door();
		FRotator orginalRotation;

		UPROPERTY(EditAnywhere, Category = "Rotation Variances")
			FRotator endRotationOfVisualWarning;

		UPROPERTY(EditAnywhere, Category = "Rotation Variances")
			FRotator endRotationOfVisualDrop;

		UPROPERTY(EditAnywhere, Category = "Rotation Variances")
			FRotator rotationAtZeroInfluence;

		UPROPERTY(EditAnywhere, Category = "Rates of Visuals")
			float rateOfWarning;

		UPROPERTY(EditAnywhere, Category = "Rates of Visuals")
			float rateOfFalling;

		UPROPERTY(EditAnywhere, Category = "Rates of Visuals")
			float rateOfReset;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh of The Rotating Platform")
			class UStaticMeshComponent* rotatingMesh;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Box Trigger For Fall")
			class UBoxComponent* activationBox;
	protected:
		virtual void BeginPlay() override;

	public:
		
		UFUNCTION()
			void Collision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		virtual void interActionCommand() override;

		void beforeDropVisualDown();

		void beforeDropVisualUp();

		void platformDrop();

		void platformReset();

		UFUNCTION(BlueprintImplementableEvent)
			void playCorrectSound(int index);
};
