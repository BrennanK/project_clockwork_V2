// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "One_Way_Transporter.generated.h"

UCLASS()
class BOOK_PROJECT_API AOne_Way_Transporter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOne_Way_Transporter();
	AOne_Way_Transporter(const FObjectInitializer &ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Transporter")
		class UBoxComponent* collisionBox;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Transporter")
		class UStaticMeshComponent* Mesh;

	UFUNCTION(Category = "Collision")
		virtual void Collision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, Category= "Locations Of Movement")
		FVector originalLocation;

	UPROPERTY(EditAnywhere, Category = "Locations Of Movement")
		FVector pathStartOrEnd;

	UPROPERTY(EditAnywhere, Category = "Seconds to Transition")
		float timeToTransition;

	float lerpAlpha;
	FTimerHandle transitionTimer;
	FVector locationBeforeTransitionStart;

	FVector destinationOfMovement;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void moveToDestination();
};
