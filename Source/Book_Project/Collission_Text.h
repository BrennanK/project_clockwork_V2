// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collission_Text.generated.h"
UENUM() enum class ETextType : uint8 { oneText,MultiText};
UCLASS()
class BOOK_PROJECT_API ACollission_Text : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollission_Text();
	ACollission_Text(const FObjectInitializer &ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Text Detector")
		class UBoxComponent* triggerBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text Variables")
		int indexOfDataTableReference;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Text Variables")
		int indexOfDataTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text Variables")
		int lastIndexToSee;
	UPROPERTY(BlueprintReadOnly, Category = "Text Variables")
		class AAvatar* player;

	UPROPERTY(EditAnywhere, Category = "Type of Text Trigger")
		ETextType typeOfText;

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
		void ShowTutorialText();
	UFUNCTION(BlueprintImplementableEvent)
		void HideTutorialText();
};
