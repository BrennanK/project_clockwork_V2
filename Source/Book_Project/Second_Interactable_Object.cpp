// Fill out your copyright notice in the Description page of Project Settings.


#include "Second_Interactable_Object.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "Avatar.h"
#include "Working_Bouncepad.h"
#include "Manipulable_Object.h"
ASecond_Interactable_Object::ASecond_Interactable_Object()
{

}

ASecond_Interactable_Object::ASecond_Interactable_Object(const FObjectInitializer &ObjectInitializer):Super(ObjectInitializer)
{
	Box= CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Box"));
	model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	model->AttachTo(RootComponent);
	Box->AttachTo(model);
	Box->OnComponentBeginOverlap.AddDynamic(this, &AInteractable_Object::Collision);
	Box->OnComponentEndOverlap.AddDynamic(this, &AInteractable_Object::EndCollision); 
}

ASecond_Interactable_Object::~ASecond_Interactable_Object()
{
	Box = nullptr;
	model = nullptr;

	delete Box;
	delete model;
}

void ASecond_Interactable_Object::BeginPlay()
{
	
}

void ASecond_Interactable_Object::inheritanceExample()
{
	//GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Orange,"THE CHILD OVERRIDE WAS SUCCESSFUL");
}

void ASecond_Interactable_Object::interactionAction(AAvatar * player)
{
	for (int i = 0; i < ActorToInfluence.Num(); i++)
	{
		Cast<AManipulable_Object>(ActorToInfluence[i])->interActionCommand();
	}
}
