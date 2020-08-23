// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToRandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "EnemyCharacter.h"
#include "EnemyAI.h"
#include "NavigationSystem.h"
#include "Wander_Then_Follow_Enemy.h"
#include "Engine.h"

EBTNodeResult::Type UBTTask_MoveToRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FNavLocation randomLocation; 

	
	AEnemyAI * AIController = Cast<AEnemyAI>(OwnerComp.GetAIOwner());

	AWander_Then_Follow_Enemy* wanderingAI = Cast<AWander_Then_Follow_Enemy>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(AIController->PawnKeyID));

	if (AIController && wanderingAI)
	{
		//UNavigationSystemV1 blah = UNavigationSystemV1(;

		//UNavigationSystemV1::GetRandomPointInNavigableRadius(wanderingAI->GetActorLocation(), 1000.f, randomLocation, nullptr, 0);

		AIController->VectorKeyID=OwnerComp.GetBlackboardComponent()->GetKeyID("Location");

		OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(AIController->VectorKeyID, randomLocation.Location);

		return EBTNodeResult::Succeeded;
	}

	else
	{
		return EBTNodeResult::Failed;
	}
	
	return EBTNodeResult::Failed;

}