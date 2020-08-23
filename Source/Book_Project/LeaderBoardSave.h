// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "MyGameInstance.h"
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h" 
#include "LeaderBoardSave.generated.h"

/**
 * 
 */
UCLASS()
class BOOK_PROJECT_API ULeaderBoardSave : public USaveGame
{
	GENERATED_BODY()
	
	public:

		ULeaderBoardSave();

		UPROPERTY(EditAnywhere)
			float numberForTesting;

		UPROPERTY(EditAnywhere)
			TArray<FLeaderboardSlot> leaderboardToSave;

		UPROPERTY(EditAnywhere)
			bool completedTutorial;
};
