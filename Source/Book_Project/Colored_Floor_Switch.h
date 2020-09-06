// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Colored_Floor_Switch.generated.h"

UCLASS()
class BOOK_PROJECT_API AColored_Floor_Switch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AColored_Floor_Switch();
	AColored_Floor_Switch(const FObjectInitializer& ObjectInitializer);
	~AColored_Floor_Switch();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		class UBoxComponent* floorBox;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Item")
		class UStaticMeshComponent* Mesh;

	UFUNCTION(Category = "Collision")
		virtual void Collision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere,Category="Controller of the Switch")
		class ABlock_Switch_Controller_01* switchManager;
	bool isGreen;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
		void changePanelColorToGreen();

	UFUNCTION(BlueprintImplementableEvent)
		void playSwitchChangeColorSound();
};
