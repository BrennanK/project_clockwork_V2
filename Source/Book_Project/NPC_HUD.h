// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "NPC_HUD.generated.h"

struct Message
{FString message; float time; FColor color; Message(){time = 5.f; color = FColor::White;}
	Message(FString iMessage, float iTime, FColor iColor){message = iMessage; time = iTime; color = iColor;}};
UCLASS()
class BOOK_PROJECT_API ANPC_HUD : public AHUD
{
	GENERATED_BODY()
	

	


	public:
		struct Icon
		{
			FString name;
			UTexture2D* tex;

			Icon()
			{
				name = "UNKNOWN ICON";
				tex = 0;
			}

			Icon(FString& iName, UTexture2D* iTex)
			{
				name = iName;
				tex = iTex;
			}
		};

		struct Widget
		{
			Icon icon;
			FVector2D pos, size;
			Widget(Icon iicon)
			{
				icon = iicon;
			}
			float left() { return pos.X; };
			float right() { return pos.X + size.X; };
			float top() { return pos.Y; };
			float bottom() { return pos.Y + size.Y;};
		};
		//UPROPERTY()
			//TArray<struct Widget> piss;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUDFont")
			UFont* hudFont;
		TArray<Message> messages;
		virtual void DrawHUD() override;
		void DrawMessages(Message msg);
		void addMessage(Message msg);
		float outputWidth;
		float outputHeight;
		float pad;
		void DrawWidgets();

};
