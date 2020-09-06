// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Distortion_Fragments.generated.h"
UENUM() enum class EPickupType:uint8{DistortionFragments,TimeAbilityShards,Lives};
UCLASS()
class BOOK_PROJECT_API ADistortion_Fragments : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADistortion_Fragments();
	ADistortion_Fragments(const FObjectInitializer& ObjectInitializer);
	~ADistortion_Fragments();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectible Properties")
		class USphereComponent* sphereCollider;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectible Properties")
		class UStaticMeshComponent* Mesh;

	UPROPERTY(EditANywhere,BlueprintReadOnly,Category = "Distortion Fragment Value")
		int fragmentValue;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		class AUI_Data_Holder* UI_Data_Container;
	UPROPERTY(EditAnywhere,Category="UI test")
		EPickupType typeOfPickUp;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void decideWhatToIncrementInUIDataHolder();

	UFUNCTION()
		void Collision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
