// Fill out your copyright notice in the Description page of Project Settings.

#include "Avatar.h"
#include "Components/InputComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/Engine.h"
#include "PickupItem.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SplineComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Collission_Text.h"
#include "Interactable_Object.h"
#include "Components/SplineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Grindable_Rail.h"
#include "Lock_On_Actor.h"
#include "Kismet/KismetMathLibrary.h"
#include "MyGameInstance.h"
#include "UI_Data_Holder.h"

// Sets default values
AAvatar::AAvatar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AAvatar::AAvatar(const FObjectInitializer& ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAvatar::BeginPlay()
{
	Super::BeginPlay();
	BaseTurnRate = 45.f;	
	teleportationParticle->DeactivateSystem();
	BaseLookRate = 45.f;
	distance = 0;
	numberOfJumps = 0;
	numberOfAlternateJumps=0;
	isCrouching = false;
	isPunching = false;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "The duration of our spline in seconds is " + FString::SanitizeFloat(ourSpline->Duration));
	currentState = ECharacterState::NORMAL;
	capsuleA->OnComponentBeginOverlap.AddDynamic(this, &AAvatar::Collision);
	firstPower = ETimeAbility::Warp;
	secondPower = ETimeAbility::Acceleration;
	originalAirControl = GetCharacterMovement()->AirControl;
}

void AAvatar::Collision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Magenta, "Yay of Player Capsule Collider works with reference YAAAAAAAAAAAAAAAAY");
	if (Cast<ACollission_Text>(OtherActor) != nullptr)
	{
		textCollider = Cast<ACollission_Text>(OtherActor);
		currentState = ECharacterState::READTEXT;
	}
	if (Cast<AInteractable_Object>(OtherActor) != nullptr)
	{
		interactable = Cast<AInteractable_Object>(OtherActor);
	}

	
	if (OtherActor->FindComponentByClass<USplineComponent>())
	{
		

		if (isGrinding == false)
		{
			ourSpline = OtherActor->FindComponentByClass<USplineComponent>();
			if (Cast<AGrindable_Rail>(OtherActor))
			{
				grindLaunchDepth = Cast<AGrindable_Rail>(OtherActor)->launchXY;
				grindLaunchHeight = Cast<AGrindable_Rail>(OtherActor)->launchZ;
				isGrinding = true;
				timeToGrind = Cast<AGrindable_Rail>(OtherActor)->secondsToSpendOnRail;
				beginGrind();
			}
		}
		
	}
}


void AAvatar::setLockOnTarget(ALock_On_Actor * target)
{
	playerTarget = target;

}

void AAvatar::removeLockOnTarget()
{
	playerTarget = nullptr;
}

void AAvatar::activateLockOnFunction()
{
	if (playerTarget == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Purple, "There is no target to lock onto");
		return;
	}


	if (isLockedOn == false)
	{
		playerTarget->indicateLock();
		//lockCameraToTarget();
		GetWorldTimerManager().SetTimer(cameraTimer, this, &AAvatar::lockCameraToTarget, GetWorld()->GetDeltaSeconds(), true, 0.0f);
		isLockedOn = true;
	}
	else
	{
		playerTarget->reverseLock();
		GetWorldTimerManager().ClearTimer(cameraTimer);
		FRotator actorRotation = GetActorRotation();
		FRotator controllerRotation = GetWorld()->GetFirstPlayerController()->GetControlRotation();
		GetWorld()->GetFirstPlayerController()->SetControlRotation(FRotator(controllerRotation.Pitch,controllerRotation.Yaw,actorRotation.Roll));
		isLockedOn = false;
	}
}

void AAvatar::lockCameraToTarget()
{
	/*if (distance <= 1)
	{
		distance += GetWorld()->GetDeltaSeconds();
		distance = FMath::Clamp(distance, 0.f, 1.f);
	}*/
	APlayerController* PController = GetWorld()->GetFirstPlayerController();

	FRotator controllerRotation = PController->GetControlRotation();
	
	FVector cameraLocation=playerCamera->GetComponentLocation();

	FVector targetLocation = playerTarget->GetActorLocation();

	FRotator playerLookingAtTarget = UKismetMathLibrary::FindLookAtRotation(cameraLocation, targetLocation);

	FRotator ZrotationNeeded = UKismetMathLibrary::RInterpTo(controllerRotation, playerLookingAtTarget, 1.f, .7f);

	PController->SetControlRotation(FRotator(controllerRotation.Pitch, ZrotationNeeded.Yaw, controllerRotation.Roll));
}

void AAvatar::LeftTimePower()
{
	if (currentState == ECharacterState::NORMAL)
	{
		useTimePower(firstPower);
	}
}

void AAvatar::RightTimePower()
{
	if (currentState == ECharacterState::NORMAL)
	{
		useTimePower(secondPower);
	}
}

void AAvatar::useTimePower(ETimeAbility ability)
{
	float* cost;
	switch (ability)
	{
	case ETimeAbility::Acceleration:
		if (continuousPowerOn == false)
		{
			if (currentEnergy >= *PowerCost.Find("Time Acceleration"))
			{
				continuousPowerOn = true;
				changeToAccelMaterial();
				GetWorldTimerManager().SetTimer(continuousPowerHandle, this, &AAvatar::subtractEnergyCost, delayBetweenDecay, true, 0.0f);
				regularWalkingSpeed = GetCharacterMovement()->MaxWalkSpeed;
				GetCharacterMovement()->MaxWalkSpeed = increasedSpeed;
			}
		}
		else
		{
			continuousPowerOn = false;
			changeToNormalMaterial();
			GetWorldTimerManager().ClearTimer(continuousPowerHandle);
			GetCharacterMovement()->MaxWalkSpeed = regularWalkingSpeed;
		}
		break;

	case ETimeAbility::Barrier:
		break;

	case ETimeAbility::Mold:
		break;

	case ETimeAbility::None:
		break;

	case ETimeAbility::Repair:
		break;

	case ETimeAbility::Stasis:
		break;

	case ETimeAbility::Warp:
		if (continuousPowerOn == true)
		{
			shutOffContinuousTimePower();
		}
		if (playerTarget != nullptr && isWarping==false)
		{
			cost = PowerCost.Find("Time Warp");
			currentEnergy -= *cost;
			callEnergyBarChange();
			lerpToDestination();
		}
		break;

	case ETimeAbility::Water:
		break;
	}
}

void AAvatar::subtractEnergyCost()
{
	if (currentEnergy >= *PowerCost.Find("Time Acceleration"))
	{
		float* cost = cost = PowerCost.Find("Time Acceleration");
		currentEnergy -= *cost;
		callEnergyBarChange();
	}
	else
	{
		shutOffContinuousTimePower();
	}
}

void AAvatar::shutOffContinuousTimePower()
{
	continuousPowerOn = false;
	changeToNormalMaterial();
	GetWorldTimerManager().ClearTimer(continuousPowerHandle);

	if (firstPower==ETimeAbility::Acceleration || secondPower==ETimeAbility::Acceleration)
	{
		GetCharacterMovement()->MaxWalkSpeed = regularWalkingSpeed;
	}
}

void AAvatar::changeToBouncePadAirControl()
{
	GetCharacterMovement()->AirControl = airControlOnBouncePad;
}

void AAvatar::addKnockback(FRotator rotationOfHarmfulObject)
{
	FRotator Rotation = rotationOfHarmfulObject;
	const FRotator YawRotation(0, Rotation.Yaw, 0);


	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	activatePlayerActionSound(4);
	ACharacter::LaunchCharacter(FVector(Direction.X * XYKnockback, Direction.Y * XYKnockback, ZKnockback), true, true);
}

void AAvatar::Landed(const FHitResult & Hit)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on screen message!"));
	numberOfJumps = 0;
	numberOfAlternateJumps = 0;
	isFalling = false;
	timeFalling = 0.0f;
	if (GetCharacterMovement()->AirControl != originalAirControl)
	{
		GetCharacterMovement()->AirControl = originalAirControl;
	}
	
}

void AAvatar::Falling()
{
	isFalling = true;
}

// Called every frame
void AAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isFalling == true)
	{
		timeFalling += DeltaTime;
	}

	if (isPaused == false)
	{
		playTime += DeltaTime;
	}
}

// Called to bind functionality to input
void AAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) //Sets up player inputs by creating key binds
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//Axis To Be Bound
	PlayerInputComponent->BindAxis("Forward", this, &AAvatar::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &AAvatar::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookupRate", this, &AAvatar::LookUpAtRate);
	PlayerInputComponent->BindAxis("TurnRate", this, &AAvatar::TurnAtRate);

	// Actions to be bound
	//PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AAvatar::ToggleInventory);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AAvatar::Jump);
	PlayerInputComponent->BindAction("Punch", IE_Pressed, this, &AAvatar::startPunching);
	PlayerInputComponent->BindAction("Punch", IE_Released, this, &AAvatar::stopPunching);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AAvatar::startCrouching);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AAvatar::stopCrouching);
	PlayerInputComponent->BindAction("Check Collectables", IE_Pressed, this, &AAvatar::showCollectables);
	PlayerInputComponent->BindAction("Change Time Powers", IE_Pressed, this, &AAvatar::changeTimePowers);
	PlayerInputComponent->BindAction("Left Time Power", IE_Pressed, this, &AAvatar::LeftTimePower);
	PlayerInputComponent->BindAction("Right Time Power", IE_Pressed, this, &AAvatar::RightTimePower);
	PlayerInputComponent->BindAction("Lock onto Target", IE_Pressed, this, &AAvatar::activateLockOnFunction);
	//PlayerInputComponent->BindAction("Crouch", IE_Repeat, this, &AAvatar::repeatCrouching);
	//Touch Control bound
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AAvatar::TouchStarted);
}

#pragma region Character_Actions
void AAvatar::MoveForward(float amount)      // detemines which direction is forward and moves actor in that direction by a specified amount
{
	switch (currentState)
	{
	case ECharacterState::NORMAL:

		if (Controller && amount != 0)
		{
			// find out which way is right
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			// add movement in that direction
			AddMovementInput(Direction, amount);
		}
		break;

	case ECharacterState::INTERACTABLE:
		if (Controller && amount != 0)
		{
			// find out which way is right
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			// add movement in that direction
			AddMovementInput(Direction, amount);
		}
		break;

	case ECharacterState::READTEXT:
		break;
	}
}

void AAvatar::MoveRight(float amount)  // determines which directions is right and moves actor in that direction by a specified amount
{
	switch (currentState)
	{
		case ECharacterState::NORMAL:
			if (Controller && amount != 0)
			{
			// find out which way is right
				const FRotator Rotation = Controller->GetControlRotation();
				const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get right vector 
				const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
				AddMovementInput(Direction, amount);
			}
			break;
		
		case ECharacterState::INTERACTABLE:
			if (Controller && amount != 0)
			{
				// find out which way is right
				const FRotator Rotation = Controller->GetControlRotation();
				const FRotator YawRotation(0, Rotation.Yaw, 0);

				// get right vector 
				const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
				// add movement in that direction
				AddMovementInput(Direction, amount);
			}
			break;

		case ECharacterState::READTEXT:
			break;
	}
}


void AAvatar::TurnAtRate(float Rate)  // Method for camera rotation on Z-axis
{
	switch (currentState)
	{
	case ECharacterState::NORMAL:
		if (isGrinding == false)
		{
			AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
			FVector cameraRotation = playerCamera->GetComponentLocation();
		}
		break;

	case ECharacterState::INTERACTABLE:
		if (isGrinding == false)
		{
			AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
		}
		break;

	case ECharacterState::READTEXT:
		break;
	}
	
}

void AAvatar::LookUpAtRate(float Rate) // Method for camera rotation on Y-axis
{
	switch (currentState)
	{
	case ECharacterState::NORMAL:
		if (isGrinding == false)
		{
			AddControllerPitchInput(Rate * BaseLookRate * GetWorld()->GetDeltaSeconds());
		}
		break;

	case ECharacterState::INTERACTABLE:
		if (isGrinding == false)
		{
			AddControllerPitchInput(Rate * BaseLookRate * GetWorld()->GetDeltaSeconds());
		}
		break;

	case ECharacterState::READTEXT:
		break;
	}
	
}

void AAvatar::printContentsOfBackpackOnScreen() // debug method of printing packpack contents
{
	int count = 0;
	for (TMap<FString, int>::TIterator it = Backpack.CreateIterator(); it; ++it)  // Iterator to print backpack contents
	{
		GEngine->AddOnScreenDebugMessage(count++, 5.f, FColor::Green, it->Key + ": " + FString::FromInt(it->Value));
	}
}

void AAvatar::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)  // method for allowing player character jump for touch screen
{
	if (FingerIndex == ETouchIndex::Touch1) // Checks to see if only one finger is used to jump
	{
		Jump();
	}
}

void AAvatar::spawnPunchingProjectile()
{
	FActorSpawnParameters SpawnParams;
	GetWorld()->SpawnActor<AActor>(AttackProjectiles[0], GetActorLocation() + GetActorForwardVector() * 50, GetActorRotation(), SpawnParams);
}

void AAvatar::startPunching()  // sets the controller varaible for our punching animation to true and enables fist collision
{
	//FActorSpawnParameters SpawnParams;
	switch (currentState)
	{
	case ECharacterState::NORMAL:
		isPunching = true;
		enableAndDisableCollision();
		//GetWorld()->SpawnActor<AActor>(AttackProjectiles[0], GetActorLocation()+GetActorForwardVector()*50, GetActorRotation(), SpawnParams);
		break;

	case ECharacterState::INTERACTABLE:
		break;

	case ECharacterState::READTEXT:
		break;
	}
}

void AAvatar::stopPunching() // sets the controller variable for our punching animation to false and disabales fist collision
{
	switch (currentState)
	{
	case ECharacterState::NORMAL:
		isPunching = false;
		enableAndDisableCollision();
		break;

	case ECharacterState::INTERACTABLE:
		break;

	case ECharacterState::READTEXT:
		break;
	}
}

void AAvatar::startCrouching()
{
	switch (currentState)
	{
	case ECharacterState::NORMAL:
		if (GetCharacterMovement()->IsMovingOnGround())
		{
			isCrouching = true;
		}
		break;

	case ECharacterState::INTERACTABLE:
		break;

	case ECharacterState::READTEXT:
		break;
	}
}

void AAvatar::stopCrouching()
{
	switch (currentState)
	{
	case ECharacterState::NORMAL:
		isCrouching = false;
		break;

	case ECharacterState::INTERACTABLE:
		break;

	case ECharacterState::READTEXT:
		break;
	}
}

//void AAvatar::repeatCrouching()
//{
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("We are repeat crouching"));
//}

#pragma endregion Charect_Actions

#pragma region MovingTeleport
void AAvatar::lerpToDestination()
{
	if (playerTarget == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Purple, "There is no target to lock onto");
		return;
	}
	GetCharacterMovement()->GravityScale = 0;
	//skeleton->SetVisibility(false);
	//teleportationParticle->ActivateSystem();
	//teleportationParticle->Activate(true);
	locationToGoTo = playerTarget->VectorOffset+playerTarget->GetActorLocation();
	locationBeforeWarp = GetActorLocation();
	changeToWarpMaterial();
	activatePlayerActionSound(5);
	isWarping = true;
	GetWorldTimerManager().SetTimer(testTimer, this, &AAvatar::transition, GetWorld()->GetDeltaSeconds(), true, 0.0f);
}


void AAvatar::transition()
{
	distance += GetWorld()->GetDeltaSeconds()/warpTimeInSeconds;
	distance=FMath::Clamp(distance, 0.f, 1.f);
	FVector newLocation=FMath::Lerp(locationBeforeWarp, locationToGoTo, distance);
	SetActorLocation(newLocation);
	
	if (distance >= 1.f || GetActorLocation().Equals(locationToGoTo,0.0f))
	{
		activatePlayerActionSound(6);
		GetWorldTimerManager().ClearTimer(testTimer);
		GetCharacterMovement()->GravityScale = 1;
		if (isLockedOn == true)
		{
			activateLockOnFunction();
		}
		//activateLockOnFunction();
		changeToNormalMaterial();
		isLockedOn = false;
		//teleportationParticle->DeactivateSystem();
		//skeleton->SetVisibility(true);
		distance = 0;
		GetCharacterMovement()->Velocity = FVector(0, 0, 0);
		isWarping = false;
	}
}
#pragma endregion MovingTeleport

#pragma region Character_Grinding
void AAvatar::beginGrind() // method to start the timer and begin rail grinding
{
	GetCharacterMovement()->GravityScale = 0;

	// Disables Pawn Control Rotator such that the camera will auto-align behind the player
	cameraBoom->bUsePawnControlRotation = false;
	
	// Returns and stores the distance along the spline in a 0 to Max count number of Spline minus 1 
	float distanceOnContact=ourSpline->FindInputKeyClosestToWorldLocation(GetActorLocation());
	
	// Calculates and sets distance for moving along the spline
	float splineDenominator = ourSpline->GetNumberOfSplinePoints() - 1;
	distance = distanceOnContact / splineDenominator;

	// Finds the location along spline based on contact point and aligns our character
	FVector grindPointStartLocation = ourSpline->GetLocationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World);
	SetActorLocation(grindPointStartLocation);

	// Begin audio for grinding
	activateGrindSound();

	// Start timer to begin grinding
	GetWorldTimerManager().SetTimer(railTimer, this, &AAvatar::grind, GetWorld()->GetDeltaSeconds(), true, 0.0f);
	//GetCharacterMovement()->GravityScale = 0;
}

void AAvatar::grind() // method for grinding along the rail
{
	// Adds a value between 0 and 1 to a float in order to assist calculating how far along the spline we should be
	// Also clamps the value so we do not go over 1 for our linear interpolation
	//distance += percentOfMovement/100;
	distance += (GetWorld()->GetDeltaSeconds()) / timeToGrind;
	distance = FMath::Clamp(distance, 0.f, 1.f);

	

	// Obtains full length of spline
	float fullLength = ourSpline->GetSplineLength();

	// Obtains a calculated value of how far along the spline from 0 to max spline length our character should be
	float calculatedLerp = FMath::Lerp(0.f, fullLength, distance);

	//Calculates two vectors to represent the vector for character position and character rotation along spline 
	FVector newestLocation = ourSpline->GetLocationAtDistanceAlongSpline(calculatedLerp, ESplineCoordinateSpace::World);
	FRotator newestRotation = ourSpline->GetRotationAtDistanceAlongSpline(calculatedLerp, ESplineCoordinateSpace::World);
	
	// Method used to set location and rotation of actor along spline, offset of 100 is used for distance of skeleton center from rail
	SetActorLocationAndRotation(FVector(newestLocation.X,newestLocation.Y,newestLocation.Z+75.f), newestRotation);
	//APlayerController* PController = GetWorld()->GetFirstPlayerController();
	//PController->SetControlRotation(ourSpline->GetRotationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World));

	// Clears the timer in order stop grinding and adds a hop off for our character
	if (distance >= 1.f)
	{
		// Get reference to plyer controller to reset rotation
		//PController->SetControlRotation(ourSpline->GetRotationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World));
		
		
		// Reset Gravity Scale before Jump Off
		GetCharacterMovement()->GravityScale = 1;
		
		// Clear Timer Handle and Reset distance along spline scaled to 0 to 1 float 
		GetWorldTimerManager().ClearTimer(railTimer);
		distance = 0;
		
		// Launch Character in Air ,reset usage Pawn Controller, and Grind Boolean
		ACharacter::LaunchCharacter((GetActorForwardVector()*grindLaunchDepth) + FVector(0, 0, grindLaunchHeight), true, true);
		deactivateGrindSound();
		cameraBoom->bUsePawnControlRotation = true;
		AController* controller = GetController();
		controller->SetControlRotation(GetActorRotation());
		isGrinding = false;
	}
}
void AAvatar::MinusHealth(float damageTaken)
{
	currentHealth -= damageTaken;
	if (currentHealth <= 0)
	{
		startDeathSequence();
	}
	callWheelChange();
}

void AAvatar::startDeathSequence()
{
	UMyGameInstance* gameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());

	if (gameInstance == nullptr)
	{
		return;
	}

	gameInstance->incrementDeathNumber();

	playDeathFade();
}

void AAvatar::ResetPlayer()
{
	UMyGameInstance* gameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());

	SetActorLocation(gameInstance->Location);

	SetActorRotation(gameInstance->Rotation);

	currentHealth = maxHealth;

	currentEnergy = maxEnergy;

	callWheelChange();

	callEnergyBarChange();

	GetRootComponent()->ComponentVelocity = FVector(0, 0, 0);
	APlayerController* PController = GetWorld()->GetFirstPlayerController();

	if (PController == nullptr)
	{
		return;
	}
	PController->SetControlRotation(gameInstance->Rotation);

	AUI_Data_Holder* UI_Data_Container = Cast<AUI_Data_Holder>(UGameplayStatics::GetActorOfClass(GetWorld(), AUI_Data_Holder::StaticClass()));
	UI_Data_Container->decrementLifeCount();
}

void AAvatar::MinusEnergy()
{
	float energyUsed = 5.f;
	currentEnergy -= energyUsed;
	callEnergyBarChange();
}

#pragma endregion CHaracter_Grinding

#pragma region Jump


void AAvatar::Jump() // method used to allow the player character to jump
{
	switch (currentState)
	{
	case ECharacterState::NORMAL:
	
		// Segment to determine whether it is a High Jump or a Long Jump
		if (isCrouching == true && numberOfAlternateJumps == 0)
		{
			if (FMath::Abs(GetCharacterMovement()->Velocity.X) > 400 || FMath::Abs(GetCharacterMovement()->Velocity.Y) > 400) // Long Jump segment
			{
				const FRotator Rotation = capsuleA->GetComponentRotation();//Controller->GetControlRotation();
				const FRotator YawRotation(0, Rotation.Yaw, 0);

				
				const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

				activatePlayerActionSound(2);
				ACharacter::LaunchCharacter(FVector(Direction.X*longJumpVelocityXY, Direction.Y*longJumpVelocityXY, longJumpHeight), false, true);
				numberOfAlternateJumps++;
			}
			else // High Jump Segment
			{
				ACharacter::LaunchCharacter(FVector(0, 0, highJumpHeight), false, true);
				activatePlayerActionSound(2);
				numberOfAlternateJumps++;
			}

		}

		// Regular Jump/Double Jump segment
		if (numberOfJumps < 2 && numberOfAlternateJumps == 0)
		{
			const FRotator Rotation = capsuleA->GetComponentRotation();//Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);


			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			if (numberOfJumps == 0)
			{
				ACharacter::LaunchCharacter(FVector(Direction.X*FMath::Abs(GetCharacterMovement()->Velocity.X), Direction.Y*FMath::Abs(GetCharacterMovement()->Velocity.Y), JumpHeight), true, true);
				activatePlayerActionSound(0);
			}
			else
			{
				ACharacter::LaunchCharacter(FVector(Direction.X, Direction.Y, JumpHeight), false, true);
				activatePlayerActionSound(1);
			}
			numberOfJumps++;
		}
		break;

	case ECharacterState::INTERACTABLE:
		interactable->interactionAction(this);
		break;

	case ECharacterState::READTEXT:
		switch (textCollider->typeOfText)
		{
		case ETextType::oneText:
			textCollider->HideTutorialText();
			currentState = ECharacterState::NORMAL;
			break;

		case ETextType::MultiText:
			if (textCollider->indexOfDataTable != textCollider->lastIndexToSee)
			{
				textCollider->indexOfDataTable += 1;
				textCollider->ShowTutorialText();
			}
			else
			{
				textCollider->HideTutorialText();
				currentState = ECharacterState::NORMAL;
			}
			break;
		}
		break;
	}
}

#pragma endregion Jump

