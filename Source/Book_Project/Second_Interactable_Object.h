// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable_Object.h"
#include "Second_Interactable_Object.generated.h"

/**
 * 
 */
UCLASS()
class BOOK_PROJECT_API ASecond_Interactable_Object : public AInteractable_Object
{
	GENERATED_BODY()


public:
	ASecond_Interactable_Object();
	ASecond_Interactable_Object(const FObjectInitializer &ObjectInitializer);
	~ASecond_Interactable_Object();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable Properties")
		class UBoxComponent* Box;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable Properties")
		class UStaticMeshComponent* model;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void inheritanceExample() override;

	//UFUNCTION()
	virtual void interactionAction(AAvatar* player)override;

};
