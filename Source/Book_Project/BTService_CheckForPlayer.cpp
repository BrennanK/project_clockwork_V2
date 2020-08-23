// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckForPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EnemyCharacter.h"
#include "Patrolling_Enemy.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "EnemyAI.h"
#include "Avatar.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"

UBTService_CheckForPlayer::UBTService_CheckForPlayer()
{
	bCreateNodeInstance = true;
	isDetonating = false;
}

void UBTService_CheckForPlayer::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, "The update node for the AI is running");
	AEnemyAI *EnemyPC = Cast<AEnemyAI>(OwnerComp.GetAIOwner());


	if (EnemyPC)
	{
		AAvatar *ourPlayer = Cast<AAvatar>(GetWorld()->GetFirstPlayerController()->GetPawn());
		APatrolling_Enemy *patroller = Cast<APatrolling_Enemy>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(EnemyPC->PawnKeyID));

		if (patroller && isDetonating==false)
		{
			GEngine->AddOnScreenDebugMessage(-1, 7.f, FColor::Orange, "We found the enemy and should be changing color");
			patroller->changeToSelfDestructMaterial();
			patroller->DestroyThisUnit();
			isDetonating = true;
		}

		if (ourPlayer)
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(EnemyPC->EnemyKeyID, ourPlayer);
			//GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Blue,"Our AI has found the player");
		}
	}
}
