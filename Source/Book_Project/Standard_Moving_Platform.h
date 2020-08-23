// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Standard_Moving_Platform.generated.h"
//UENUM() enum class EDIRECTIONOFMOVEMENT : uint8 { X,Y,Z };
UCLASS()
class BOOK_PROJECT_API AStandard_Moving_Platform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStandard_Moving_Platform();

	UPROPERTY(EditAnywhere, Category = "Movement Variables")
	EDIRECTIONOFMOVEMENT direction;

	UPROPERTY(EditAnywhere, Category = "Movement Variables")
		float amountToMove;

	UPROPERTY(EditAnywhere, Category = "Movement Variables")
		float rangeOfMovement;

	float originalX;
	float originalY;
	float originalZ;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
