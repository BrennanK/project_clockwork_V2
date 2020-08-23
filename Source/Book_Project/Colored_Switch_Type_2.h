// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Colored_Floor_Switch.h"
#include "Colored_Switch_Type_2.generated.h"

/**
 * 
 */
UCLASS()
class BOOK_PROJECT_API AColored_Switch_Type_2 : public AColored_Floor_Switch
{
	GENERATED_BODY()
	
	public:

		virtual void Collision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)override;
		
		UFUNCTION(BlueprintImplementableEvent)
			void changeToBluePanel();

		UFUNCTION(BlueprintImplementableEvent)
			void changeToOrangePanel();

		UFUNCTION(BlueprintImplementableEvent)
			void playFloorSwitchSound();
};
