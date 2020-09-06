// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manipulable_Object.h"
#include "NewBounce_Pad.generated.h"

/**
 */ 
UENUM() enum class EBOUNCE :uint8 { Single, Build_Up };
UCLASS()
class BOOK_PROJECT_API ANewBounce_Pad : public AManipulable_Object
{
	GENERATED_BODY()
	
	public:
		ANewBounce_Pad();
		ANewBounce_Pad(const FObjectInitializer& ObjectInitializer);
		~ANewBounce_Pad();

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
			class UBoxComponent* bounceBox;

		UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
			class UStaticMeshComponent* Mesh;

		UPROPERTY(EditAnywhere, Category = "Bounce Variables")
			float minBounceHeight;

		UPROPERTY(EditAnywhere, Category = "Bounce Variables")
			float maxBounceHeight;

		UPROPERTY(EditAnywhere, Category = "Bounce Variables")
			float bounceHeightPerSecondFalling;

		/*UPROPERTY(EditAnywhere, Category = "Type of Bounce_Pad")
			EBOUNCE padType;*/

		UPROPERTY(EditAnywhere, Category = "Bounce Type")
			EBOUNCE typeOfPad;

		//float lerpAlpha;
	protected:
		virtual void BeginPlay() override;
	public:
		UFUNCTION()
			void Collision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		UFUNCTION()
			void EndCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

		//UFUNCTION()
		virtual void interActionCommand()override;

		//UFUNCTION()
		virtual void Move()override;
};
