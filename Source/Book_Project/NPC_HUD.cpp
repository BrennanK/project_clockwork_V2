// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC_HUD.h"
#include "Engine/Engine.h"
#include "Engine/Canvas.h"
void ANPC_HUD::DrawHUD()
{
	Super::DrawHUD();
	
	/*DrawLine(200, 300, 400, 500, FLinearColor::Blue);
	DrawText("Greetings from Unreal!", FLinearColor::White, 400, 200, hudFont);*/
	
}

void ANPC_HUD::DrawMessages(Message msg)
{
	for (int c = messages.Num() - 1; c >= 0; c--)
	{
		outputWidth, outputHeight, pad = 10.f;
		GetTextSize(messages[c].message, outputWidth, outputHeight, hudFont, 1.f);
		float messageH = outputHeight + 2.f*pad;
		float x = 0.f, y = c * messageH;

		DrawRect(FLinearColor::Black, x, y, Canvas->SizeX, messageH);
		DrawText(messages[c].message, messages[c].color, x + pad, y + pad, hudFont);

		messages[c].time -= GetWorld()->GetDeltaSeconds();

		if (messages[c].time < 0)
		{
			messages.RemoveAt(c);
		}
	}
}

void ANPC_HUD::addMessage(Message msg)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Add message is being called")));
	messages.Add(msg);
	//DrawMessages(msg);
	//DrawHUD();
	//DrawText("Blah", msg.color, 400, 200, hudFont);
}

 
