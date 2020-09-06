// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable_Object.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "Avatar.h"

// Sets default values
AInteractable_Object::AInteractable_Object()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
AInteractable_Object::AInteractable_Object(const FObjectInitializer &ObjectInitializer): Super(ObjectInitializer)
{
	
}
AInteractable_Object::~AInteractable_Object()
{
	for (int i = 0; i < ActorToInfluence.Num(); i++)
	{
		ActorToInfluence[i] = nullptr;
		delete ActorToInfluence[i];
	}
}
// Called when the game starts or when spawned
void AInteractable_Object::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractable_Object::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractable_Object::Collision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return;
	}
	AAvatar* player = Cast<AAvatar>(OtherActor);
	player->currentState = ECharacterState::INTERACTABLE;
	displayInteractionIcon();
}

void AInteractable_Object::EndCollision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return;
	}
	hideInteractionIcon();
	AAvatar* player = Cast<AAvatar>(OtherActor);
	player->currentState = ECharacterState::NORMAL;
}

void AInteractable_Object::interactionAction(AAvatar* player)
{
	player->currentState = ECharacterState::INTERACTABLE;
}

void AInteractable_Object::inheritanceExample()
{

}

