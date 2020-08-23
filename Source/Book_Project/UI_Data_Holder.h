// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UI_Data_Holder.generated.h"

UCLASS()
class BOOK_PROJECT_API AUI_Data_Holder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUI_Data_Holder();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player UI variables")
		int D_Frag_Count;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player UI variables")
		int TA_Frag_Count;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player UI variables")
		int Life_Obtained_Count;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player UI variables")
		int D_Frag_MaxValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player UI variables")
		int TA_Frag_MaxValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player UI variables")
		int Lives_MaxValue;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void incrementD_FragCount(int valueOfFragment);
	void incrementTA_FragCount();
	void incrementLifeCount();
	void decrementLifeCount();

	UFUNCTION(BlueprintImplementableEvent)
		void updateFragmentCount(int shardWorth);

	UFUNCTION(BlueprintImplementableEvent)
		void updateAbilityShardCount();

	UFUNCTION(BlueprintImplementableEvent)
		void updateLifeCount();
	
	/*UFUNCTION(BlueprintImplementableEvent)
		void decrementLifeCount();*/


};
