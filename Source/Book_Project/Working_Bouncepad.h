// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Working_Bouncepad.generated.h"
//UENUM() enum class EBOUNCE_TYPE:uint8 {Single,Build_Up};
UCLASS()
class BOOK_PROJECT_API AWorking_Bouncepad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorking_Bouncepad();
	AWorking_Bouncepad(const FObjectInitializer& ObjectInitializer);


	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "Components")
		class UBoxComponent* bounceBox;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
		class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Bounce Variables")
		float minBounceHeight;

	UPROPERTY(EditAnywhere, Category = "Bounce Variables")
		float maxBounceHeight;
	
	UPROPERTY(EditAnywhere, Category = "Bounce Variables")
		float bounceHeightPerSecondFalling;
	
	//UPROPERTY(EditAnywhere, Category = "Type of Bounce_Pad")
		//EBOUNCE_TYPE padType;

	float lerpAlpha;

	UPROPERTY(VisibleAnywhere, Category="Bouncepad starting point")
	FVector originalLocation;

	UPROPERTY(EditAnywhere)
		FVector destination;

	FTimerHandle movementTimer;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION()
	//void Collision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//UFUNCTION()
	//	void EndCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	////UFUNCTION()
	//	virtual void interActionCommand();
	//
	////UFUNCTION()
	//	virtual void Move();

	UFUNCTION(BlueprintImplementableEvent)
		void changeCameraPerspective();
};
