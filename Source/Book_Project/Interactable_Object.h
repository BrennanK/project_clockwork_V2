// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Avatar.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable_Object.generated.h"
UENUM() enum class EInteractionType: uint8{ANIMATION,SPAWN};
UCLASS()
class BOOK_PROJECT_API AInteractable_Object : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable_Object();
	AInteractable_Object(const FObjectInitializer &ObjectInitializer);

	UPROPERTY(EditAnywhere, Category = "Actor to Spawn")
		TArray<AActor*> ActorToInfluence;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable Properties")
		class UBoxComponent* interBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable Properties")
		class UStaticMeshComponent* mesh;*/

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trial of Link")
		class ADistortion_Fragments* frag;*/
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void Collision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent)
		void displayInteractionIcon();

	UFUNCTION(BlueprintImplementableEvent)
		void hideInteractionIcon();

	UFUNCTION()
		virtual void interactionAction(AAvatar* player);

	UFUNCTION()
		virtual void inheritanceExample();
};
