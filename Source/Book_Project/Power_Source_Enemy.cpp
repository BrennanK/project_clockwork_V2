// Fill out your copyright notice in the Description page of Project Settings.


#include "Power_Source_Enemy.h"
#include "Avatar.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"
#include "EnemyAI.h"
#include "Engine.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BehaviorTree/BehaviorTree.h"
#include "TimerManager.h"
#include "Enemy_Spawner.h"

APower_Source_Enemy::APower_Source_Enemy()
{

}

APower_Source_Enemy::APower_Source_Enemy(const FObjectInitializer &ObjectInitializer) :Super(ObjectInitializer)
{
	//capsuleCollider->OnComponentBeginOverlap.AddDynamic(this, &APower_Source_Enemy::Collision);
}

void APower_Source_Enemy::Collision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 7.f, FColor::Orange, "Our power enemy is colliding with something");
	if (Cast<AAvatar>(OtherActor) && damagedAlready==false)
	{
		damagedAlready = true;
		AAvatar* player = Cast<AAvatar>(OtherActor);

		player->MinusHealth(damageToPlayer);

		FRotator directionOfPlayer= UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), player->GetActorLocation());

		AEnemyAI* controller = Cast<AEnemyAI>(GetController());

		controller->returnBlackboard()->SetValue<UBlackboardKeyType_Bool>(controller->BoolForChasingID, false);

		GetWorldTimerManager().SetTimer(delayForChaseHandler, this, &APower_Source_Enemy::startChasingAgain, 1.0f, false, delayOfChase);

		player->addKnockback(directionOfPlayer);
	}
}

void APower_Source_Enemy::Die()
{
	if (isRespawnable == true)
	{
		delayOfRespawn = 1.0f;
		spawnerRef->spawnEnemyAfterDelay(delayOfRespawn);
	}
	Destroy();
}

void APower_Source_Enemy::BeginPlay()
{
	Super::BeginPlay();
	capsuleCollider->OnComponentBeginOverlap.AddDynamic(this, &APower_Source_Enemy::Collision);
	if (Cast<AEnemyAI>(GetController()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 7.f, FColor::Orange, "I have obtained the enemy AI controller via casting");

		startChasingAgain();
	}
}

void APower_Source_Enemy::startChasingAgain()
{
	GEngine->AddOnScreenDebugMessage(-1, 7.f, FColor::Orange, "We are calling set chase to true");
	AEnemyAI* controller = Cast<AEnemyAI>(GetController());

	controller->returnBlackboard()->SetValue<UBlackboardKeyType_Bool>(controller->BoolForChasingID, true);

	damagedAlready = false;
}
