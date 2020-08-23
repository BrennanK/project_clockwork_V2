// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupItem.generated.h"

UCLASS()
class BOOK_PROJECT_API APickupItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupItem();
	APickupItem(const FObjectInitializer& ObjectInitializer);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		int32 Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		class USphereComponent* ProxSphere;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Item")
		class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		UTexture2D* Icon;

	UFUNCTION(Category = "Collision")
		void Prox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
