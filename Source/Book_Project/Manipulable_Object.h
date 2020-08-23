// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Manipulable_Object.generated.h"
//UENUM() enum class EBOUNCE :uint8 { Single, Build_Up };
UCLASS()
class BOOK_PROJECT_API AManipulable_Object : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AManipulable_Object();
	AManipulable_Object(const FObjectInitializer& ObjectInitializer);
	UPROPERTY(VisibleAnywhere, Category = "Bouncepad starting point")
		FVector originalLocation;

	UPROPERTY(EditAnywhere)
		FVector destination;

	FTimerHandle movementTimer;

	float lerpAlpha;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void interActionCommand();

	UFUNCTION()
		virtual void Move();

};
