// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math_Answer_Display.generated.h"

UCLASS()
class BOOK_PROJECT_API AMath_Answer_Display : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMath_Answer_Display();

private:
	UPROPERTY(EditAnywhere)
	int m;

	UPROPERTY(EditAnywhere)
	int b;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	int pointOnLine(const int &m, const  int &b, const  int &t);
	int slopeGradientCalc(int &x1, int &x2, int &y1, int &y2);

	void slopeChallenge();
};
