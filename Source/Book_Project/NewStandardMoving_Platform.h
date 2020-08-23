// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manipulable_Object.h"
#include "NewStandardMoving_Platform.generated.h"

/**
 */ 
UENUM() enum class EDIRECTIONOFMOVEMENT : uint8 { X, Y, Z };
UCLASS()
class BOOK_PROJECT_API ANewStandardMoving_Platform : public AManipulable_Object
{
	GENERATED_BODY()
	
	public:
		ANewStandardMoving_Platform();
		UPROPERTY(EditAnywhere, Category = "Movement Variables")
			EDIRECTIONOFMOVEMENT direction;

		UPROPERTY(EditAnywhere, Category = "Movement Variables")
			float amountToMove;

		UPROPERTY(EditAnywhere, Category = "Movement Variables")
			float rangeOfMovement;

		float originalX;
		float originalY;
		float originalZ;
	protected:
		virtual void BeginPlay() override;
	public:
		virtual void Tick(float DeltaTime) override;
		virtual void interActionCommand()override;
		virtual void Move()override;
};
