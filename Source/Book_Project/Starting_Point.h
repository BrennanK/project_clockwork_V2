// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Starting_Point.generated.h"

UCLASS()
class BOOK_PROJECT_API AStarting_Point : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStarting_Point();
	UPROPERTY()
		APlayerController* PController;
	UPROPERTY(EditAnywhere, Category="Initial Camera Setup")
		float initialLookRate;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
