// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "Power_Source_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class BOOK_PROJECT_API APower_Source_Enemy : public AEnemyCharacter
{
	GENERATED_BODY()
	
	public:
		APower_Source_Enemy();
		APower_Source_Enemy(const FObjectInitializer &ObjectInitializer);

		UPROPERTY(EditAnywhere)
			float damageToPlayer;

		UFUNCTION()
			void Collision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		void startChasingAgain();

		FTimerHandle delayForChaseHandler;

		UPROPERTY(EditAnywhere, Category = "Delay for ChaseAfter Damage")
			float delayOfChase;

		bool damagedAlready;

		
		virtual void Die() override;

		UFUNCTION(BlueprintImplementableEvent)
			void playPunchImpactSound();
	protected:
		virtual void BeginPlay() override;
};
