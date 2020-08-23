// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EnemyCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Engine.h"

AEnemyAI::AEnemyAI()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));

}

void AEnemyAI::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);

	AEnemyCharacter *Char = Cast<AEnemyCharacter>(InPawn);

	if (Char == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, "Our AI cast to enemy character has failed");
	}

	if (Char && Char->BotBehavior)
	{
		BlackboardComp->InitializeBlackboard(*Char->BotBehavior->BlackboardAsset);

		EnemyKeyID = BlackboardComp->GetKeyID("Target");

		PawnKeyID = BlackboardComp->GetKeyID("Pawn_Ref");

		BoolForChasingID = BlackboardComp->GetKeyID("ShouldChasePlayer");
		BehaviorComp->StartTree(*Char->BotBehavior);

		BehaviorComp->GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(PawnKeyID, Char);
	}
}

UBlackboardComponent* AEnemyAI::returnBlackboard()
{
	return BlackboardComp;
}
