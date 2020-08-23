// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "LeaderBoardSave.h"
#include "Engine.h"

void UMyGameInstance::SaveGame(TArray<FLeaderboardSlot> boardToSave, bool tutorialCompletionVar)
{
	ULeaderBoardSave* myLeaderBoard = Cast<ULeaderBoardSave>(UGameplayStatics::CreateSaveGameObject(ULeaderBoardSave::StaticClass()));

	//myLeaderBoard->numberForTesting = number;
	myLeaderBoard->leaderboardToSave = boardToSave;
	myLeaderBoard->completedTutorial = tutorialCompletionVar;
	UGameplayStatics::SaveGameToSlot(myLeaderBoard, TEXT("MyLeaderBoard"), 0);
	GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Orange, "Save has been acomplished");
}

void UMyGameInstance::LoadGame()
{
	ULeaderBoardSave* myLeaderBoard = Cast<ULeaderBoardSave>(UGameplayStatics::CreateSaveGameObject(ULeaderBoardSave::StaticClass()));

	if (Cast<ULeaderBoardSave>(UGameplayStatics::LoadGameFromSlot("MyLeaderBoard", 0)) == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Orange, "Failed to load because there was no file to load");
		GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Orange, "Creating New Leaderboard");
		createASampleBoard();
	}

	myLeaderBoard = Cast<ULeaderBoardSave>(UGameplayStatics::LoadGameFromSlot("MyLeaderBoard", 0));
	leaderboardToPresent = myLeaderBoard->leaderboardToSave;
	completionHolder = myLeaderBoard->completedTutorial;
	GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Orange, "Load has been acomplished");
}

void UMyGameInstance::saveCompletionOfTutorial()
{
	LoadGame();
	SaveGame(leaderboardToPresent,true);
}

void UMyGameInstance::createASampleBoard()
{
	FLeaderboardSlot emptySlot;
	emptySlot.name = "Bill";
	emptySlot.timeTakenToCompleteLevel =0.f;
	emptySlot.playerScore = 0;
	for (int i = 0; i < 5; i++)
	{
		leaderboardToPresent.Add(emptySlot);
	}
	SaveGame(leaderboardToPresent,false);
}

int UMyGameInstance::isNewScore(int scoreToEvaluate)
{
	float number = scoreToEvaluate;
	LoadGame();
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Orange, "This is the score being passed to checker " + FString::SanitizeFloat(number));
	for (int i = 0; i < leaderboardToPresent.Num(); i++)
	{
		if (scoreToEvaluate > leaderboardToPresent[i].playerScore)
		{
			number = leaderboardToPresent[i].playerScore;
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Orange, "This is the score of the index " + FString::SanitizeFloat(number));
			return i;
		}
	}
	return -1;
}

int UMyGameInstance::isFasterTime(float playerTimeAsAFloat)
{
	LoadGame();
	//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Orange, "This is the score being passed to checker " + FString::SanitizeFloat(number));
	for (int i = 0; i < leaderboardToPresent.Num(); i++)
	{
		if (playerTimeAsAFloat < leaderboardToPresent[i].timeTakenToCompleteLevel && leaderboardToPresent[i].timeTakenToCompleteLevel!=0.f)
		{
			//number = leaderboardToPresent[i].timeTakenToCompleteLevel;
			//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Orange, "This is the score of the index " + FString::SanitizeFloat(number));
			return i;
		}
	}
	return -1;
}

void UMyGameInstance::updateLeaderboard(int indexOfNewScore,FString playerName,float playerTime,int newHighscore)
{
	for (int i = leaderboardToPresent.Num() - 1; i > indexOfNewScore - 1; i--)
	{
		if (i == indexOfNewScore)
		{
			leaderboardToPresent[i].playerScore=newHighscore;
			leaderboardToPresent[i].name = playerName;
			leaderboardToPresent[i].timeTakenToCompleteLevel = playerTime;
		}
		else
		{
			leaderboardToPresent[i] = leaderboardToPresent[i - 1];
		}
	}
	SaveGame(leaderboardToPresent,true);
}

int UMyGameInstance::calculateBonusAmount()
{
	deserveDeathBonus();
	deserveObjectiveBonus();
	return bonusAccumulated;
}

void UMyGameInstance::incrementDeathNumber()
{
	numberOfDeaths++;
	GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Orange, "The Number of Deaths for the player is "+ FString::SanitizeFloat((float)numberOfDeaths));
}

void UMyGameInstance::deserveDeathBonus()
{
	if (numberOfDeaths == 0)
	{
		bonusAccumulated += bonusForDeaths;
	}
}

void UMyGameInstance::deserveObjectiveBonus()
{
	if (allObjectivesComplete == true)
	{
		bonusAccumulated += bonusForObjectives;
	}
}
