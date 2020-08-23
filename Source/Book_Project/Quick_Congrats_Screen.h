// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Quick_Congrats_Screen.generated.h"

UCLASS()
class BOOK_PROJECT_API AQuick_Congrats_Screen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuick_Congrats_Screen();
	AQuick_Congrats_Screen(const FObjectInitializer &ObjectInitializer);

	UPROPERTY(EditAnywhere, Category = "Congrats Collider")
		class UBoxComponent* boxCollider;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void Collision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION(BlueprintImplementableEvent)
		void showCongrats();
};
