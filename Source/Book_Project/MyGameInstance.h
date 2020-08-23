// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

USTRUCT(BlueprintType) struct FLeaderboardSlot
{GENERATED_BODY() UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leaderboard Struct") FString name; UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leaderboard Struct") float timeTakenToCompleteLevel; UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leaderboard Struct") int playerScore;
};
UCLASS()
class BOOK_PROJECT_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

	public:
		UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Game Instance Variables for DeathBox")
			FVector Location;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Instance Variables for DeathBox")
			FRotator Rotation;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Instance Variables for Bonus Attributes")
			int bonusAccumulated;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Instance Variables for Bonus Attributes")
			int numberOfDeaths;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Instance Variables for Bonus Attributes")
			bool allObjectivesComplete;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Instance Variables for Bonus Attributes")
			int bonusForDeaths;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Instance Variables for Bonus Attributes")
			int bonusForObjectives;

		UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Tutuorial Decider")
			bool completionHolder;

		UFUNCTION(BlueprintCallable)
			void SaveGame(TArray<FLeaderboardSlot> boardToSave, bool tutorialCompletionVar);
		
		UFUNCTION(BlueprintCallable)
			void LoadGame();

		UFUNCTION(BlueprintCallable)
			void saveCompletionOfTutorial();

		UFUNCTION()
			void createASampleBoard();

		UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Array of LeaderboardSlot Structs")
			TArray<FLeaderboardSlot> leaderboardToPresent;

		UFUNCTION(BlueprintCallable)
			int isNewScore(int scoreToEvaluate);

		UFUNCTION(BlueprintCallable)
			int isFasterTime(float playerTimeAsAFloat);

		UFUNCTION(BlueprintCallable)
			void updateLeaderboard(int indexOfNewScore, FString playerName, float playerTime,int newHighscore);
		
		UFUNCTION(BlueprintCallable)
			int calculateBonusAmount();

		UFUNCTION()
			void incrementDeathNumber();

		UFUNCTION()
			void deserveDeathBonus();

		UFUNCTION()
			void deserveObjectiveBonus();

		UPROPERTY()
			float musicSliderValue;

		UPROPERTY()
			float effectSliderValue;
};
