// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAI.generated.h"

/**
 * 
 */
UCLASS()
class BOOK_PROJECT_API AEnemyAI : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(transient)
	class UBlackboardComponent *BlackboardComp;

	UPROPERTY(transient)
	class UBehaviorTreeComponent *BehaviorComp;

	public:

		AEnemyAI();

		virtual void OnPossess(APawn *InPawn) override;

		uint8 EnemyKeyID;

		uint8 PawnKeyID;

		uint8 VectorKeyID;

		uint8 BoolForChasingID;

		UBlackboardComponent* returnBlackboard();
};
