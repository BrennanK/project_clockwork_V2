// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particle_Played_On_Destruction.generated.h"

UCLASS()
class BOOK_PROJECT_API AParticle_Played_On_Destruction : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParticle_Played_On_Destruction();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle To Be Played On Actor Destruction")
		class UParticleSystemComponent* particle;

	UPROPERTY(EditAnywhere, Category = "Lifetime Of Particle")
		float lifeTime;

	FTimerHandle particleTimer;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DestroyParticle();
};
