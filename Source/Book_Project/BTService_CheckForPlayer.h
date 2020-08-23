// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckForPlayer.generated.h"

/**
 * 
 */
UCLASS()
class BOOK_PROJECT_API UBTService_CheckForPlayer : public UBTService
{
	GENERATED_BODY()

	public:
		UBTService_CheckForPlayer();
		bool isDetonating;
		virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
