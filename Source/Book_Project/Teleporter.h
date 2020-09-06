// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Teleporter.generated.h"

UCLASS()
class BOOK_PROJECT_API ATeleporter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleporter();
	ATeleporter(const FObjectInitializer& ObjectInitializer);
	~ATeleporter();
	UPROPERTY(EditAnywhere,Category="Destination")
	FVector locationtoGoTo;

	UPROPERTY(EditAnywhere, Category = " Teleporter Collider")
		class USphereComponent* collider;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Teleport(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
