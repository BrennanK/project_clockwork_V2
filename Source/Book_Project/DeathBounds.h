// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeathBounds.generated.h"

UCLASS()
class BOOK_PROJECT_API ADeathBounds : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADeathBounds();
	ADeathBounds(const FObjectInitializer &ObjectInitializer);

	FVector locationToSet;
	FRotator rotationToSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Death Box Properties")
		class UBoxComponent* deathBox;

	class UMyGameInstance* gameInstance;

	class AAvatar* player;
	
	UPROPERTY(EditAnywhere)
		float testValueForSave;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void Collision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintImplementableEvent)
		void playDeathFade();

	UFUNCTION(BlueprintCallable)
		void resetPlayer();
};
