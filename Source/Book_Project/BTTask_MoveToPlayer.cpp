// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EnemyCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "EnemyAI.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine.h"
#include "Avatar.h"
EBTNodeResult::Type UBTTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAI *CharPC = Cast<AEnemyAI>(OwnerComp.GetAIOwner());

	AAvatar *Enemy = Cast<AAvatar>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(CharPC->EnemyKeyID));

	if (Enemy)
	{
		//CharPC->MoveToActor(Enemy, 5.f, true, true, true, 0, true);
		FRotator originalRotation = OwnerComp.GetOwner()->GetActorRotation();
		FRotator lookAtPlayer = UKismetMathLibrary::FindLookAtRotation(OwnerComp.GetOwner()->GetActorLocation(), Enemy->GetActorLocation());
		FRotator newRotation = FRotator(originalRotation.Pitch, lookAtPlayer.Yaw, originalRotation.Roll);
		
		CharPC->SetControlRotation(newRotation);
		OwnerComp.GetOwner()->SetActorRotation(newRotation);
		
		// Come Back to this regarding movement of character
		/*AEnemyCharacter* thisAI = Cast<AEnemyCharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(CharPC->PawnKeyID));

		if (thisAI == nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Emerald, "The cast failed my dude");
		}

		FVector Direction = FRotationMatrix(FRotator(0,lookAtPlayer.Yaw,0)).GetUnitAxis(EAxis::X);
		APawn* thisPawn=Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(CharPC->PawnKeyID));

		
		thisAI->AddMovementInput(Direction, thisAI->movementSpeed);*/
		CharPC->MoveToActor(Enemy, 20.f, false, true, true, 0, true);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}