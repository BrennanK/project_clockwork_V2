// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Punch_Projectile.generated.h"

UCLASS()
class BOOK_PROJECT_API APunch_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APunch_Projectile();
	APunch_Projectile(const FObjectInitializer &ObjectInitializer);
	~APunch_Projectile();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Variables")
		class USphereComponent* projectileCollider;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Variables")
		class UStaticMeshComponent* mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Punching Projectile Properties")
		float lifetime;

	float timeAlive;

	UPROPERTY(EditAnywhere, Category = "Punching Projectile Properties")
		float speed;
	UFUNCTION()
		void Collision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
		void showColorVisual(AEnemyCharacter* characterHit);

	UFUNCTION(BlueprintImplementableEvent)
		void playPuchSoundEffect();
};
