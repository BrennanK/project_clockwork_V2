// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "Patrolling_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class BOOK_PROJECT_API APatrolling_Enemy : public AEnemyCharacter
{
	GENERATED_BODY()
	
	public:
		APatrolling_Enemy(const FObjectInitializer &ObjectInitializer);
		~APatrolling_Enemy();
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blast Zone")
			class USphereComponent* explosionRadius;

		UPROPERTY(BlueprintReadOnly, Category = "Spawner ref")
			class AEnemy_Spawner* spawner;

		class AAvatar* playerCharacter;

		class ADestructable_Wall* wall;

		UPROPERTY(EditAnywhere, Category = "Damage Done to Player")
			float damageToDeal;
		
		FTimerHandle blinkHandle;
		
		FTimerHandle deathHandle;

		UFUNCTION(BlueprintImplementableEvent)
			void changeToSelfDestructMaterial();

		UFUNCTION(BlueprintImplementableEvent)
			void changeSpeedOfBlink();
		
		void initiateSpeedChange();

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed of Blinking Detonation")
			float fastBlinkSpeed;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed of Blinking Detonation")
			float slowBlinkSpeed;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed of Blinking Detonation")
			float secondsBetweenFastBlinkAndBlowUp;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed of Blinking Detonation")
			float slowBlinkDelay;
		void DestroyCaller();

		virtual void DestroyThisUnit() override;

		virtual void Die() override;

		UPROPERTY(EditAnywhere, Category = "Particle to Spawn")
			TSubclassOf<AActor> particleToSpawn;

		UFUNCTION()
			void Collision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		UFUNCTION()
			void EndCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

		UFUNCTION(BlueprintImplementableEvent)
			void playPunchImpactSound();

		UFUNCTION(BlueprintImplementableEvent)
			void playFuseLightSound();

		UFUNCTION(BlueprintImplementableEvent)
			void playExplosionSound();

		UFUNCTION(BlueprintImplementableEvent)
			void stopFuseLightSound();
	protected:
		virtual void BeginPlay() override;
};
