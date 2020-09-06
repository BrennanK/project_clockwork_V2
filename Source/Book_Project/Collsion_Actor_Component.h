// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Collsion_Actor_Component.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOOK_PROJECT_API UCollsion_Actor_Component : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCollsion_Actor_Component();
	UCollsion_Actor_Component(const FObjectInitializer &ObjectInitializer);
	~UCollsion_Actor_Component();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collison Component Pieces")
		class UBoxComponent* triggerBox;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision Component Pieces")
		class UStaticMeshComponent* mesh;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
		void Collision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
