// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "TimerManager.h"
#include "Engine.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AEnemyCharacter::AEnemyCharacter(const FObjectInitializer &ObjectInitializer):Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::initiateDestruction(FRotator projectileRotation)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "I the enemy have been hit");

	FRotator Rotation = projectileRotation;
	const FRotator YawRotation(0, Rotation.Yaw, 0);


	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	ACharacter::LaunchCharacter(FVector(Direction.X * XYKnockback, Direction.Y * XYKnockback, ZKnockback),true,true);

	GetWorldTimerManager().SetTimer(destructionHandler,this,&AEnemyCharacter::Die,1.0f,false,delay);

}

void AEnemyCharacter::Die()
{
	Destroy();
}

void AEnemyCharacter::DestroyThisUnit()
{
	Destroy();
}

