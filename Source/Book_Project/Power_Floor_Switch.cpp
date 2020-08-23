// Fill out your copyright notice in the Description page of Project Settings.


#include "Power_Floor_Switch.h"
#include "Block_Switch_Controller_01.h"
#include "Power_Source_Enemy.h"

void APower_Floor_Switch::Collision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<APower_Source_Enemy>(OtherActor)==nullptr)
	{
		return;
	}
	if (isGreen == false)
	{
		changeToGreenPanel();
		playElectricFloorSwitchSound();
		switchManager->incrementSwitchCounter();
		isGreen = true;
		APower_Source_Enemy* power = Cast<APower_Source_Enemy>(OtherActor);
		power->spawnerRef->spawnEnemyAfterDelay(switchManager->timeToTransitionCamera + switchManager->secondsToTransition * 2);
		power->Destroy();
		
	}
}