// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manipulable_Object.h"
#include "Lock_On_Actor.generated.h"

/**
 * 
 */
UCLASS()
class BOOK_PROJECT_API ALock_On_Actor : public AManipulable_Object
{
	GENERATED_BODY()
	
	public:
		ALock_On_Actor();
		~ALock_On_Actor();
		UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Lock-On properties")
			FVector VectorOffset;

		UPROPERTY(EditAnywhere, Category = "Lock-On properties")
			float normalizationTolerence;

		UPROPERTY()
			class AAvatar* player;

		UPROPERTY(EditAnywhere, Category = "Lock-On properties")
			float closenessRange;

		UPROPERTY(EditAnywhere, Category = "Lock-On properties")
			float turnOffRange;

		UPROPERTY(EditAnywhere, Category = "Lock-On properties")
			float rangeInVectorUnits;


		float normalizedDistance;

	protected:
		virtual void BeginPlay() override;
	public:
		virtual void Tick(float DeltaTime) override;

		UFUNCTION(BlueprintImplementableEvent)
			void LockOn();

		UFUNCTION(BlueprintImplementableEvent)
			void LockOff();
		
		UFUNCTION(BlueprintImplementableEvent)
			void indicateLock();
		
		UFUNCTION(BlueprintImplementableEvent)
			void reverseLock();
};
