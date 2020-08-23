// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manipulable_Object.h"
#include "Large_Spinning_Object.generated.h"

/**
 * 
 */
UCLASS()
class BOOK_PROJECT_API ALarge_Spinning_Object : public AManipulable_Object
{
	GENERATED_BODY()
	
	public:
		ALarge_Spinning_Object();

		UPROPERTY(EditAnywhere, Category="Rotation Properties")
		float rateOfRotation;

		
			float originalRotationRate;

		UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Rotation Properties")
			float amountToRotate;

		UPROPERTY(EditAnywhere, Category = "Rotation Properties")
			float slowedRotationAmount;

		FTimerHandle spinTimer;

		FRotator currentRotation;

	protected:
		virtual void BeginPlay() override;
	public:
		void BeginSpin();

		void Spinning();

		virtual void interActionCommand() override;

};
