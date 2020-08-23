// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC.h"
#include "Avatar.h"
#include "NPC_HUD.h"
#include "Components/SphereComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
// Sets default values


ANPC::ANPC(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProxSphere=CreateDefaultSubobject<USphereComponent>(TEXT("My Sphere Collider"));
	ProxSphere->AttachTo(RootComponent);
	ProxSphere->SetSphereRadius(100);
	ProxSphere->SetHiddenInGame(true);
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &ANPC::Prox);
	NpcMessage = "Hi I'm Hank";
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Our collision works hooray")));
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPC::Prox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Our collision works hooray")));
	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return;
	}
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	if (PController)
	{
		NpcMessage = "Please print";
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("We are reaching PController if statement")));
		ANPC_HUD* hud = Cast<ANPC_HUD>(PController->GetHUD());
		//hud->addMessage(Message(NpcMessage, 5.f, FColor::White));
		//Cast<AAvatar>(OtherActor)->lerpToDestination(location);
	}
}

