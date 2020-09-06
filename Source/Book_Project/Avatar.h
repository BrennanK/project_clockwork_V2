// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Avatar.generated.h"
UENUM() enum class ETimeAbility:uint8{None,Water,Warp,Barrier,Mold,Repair,Stasis,Acceleration};
UENUM() enum class ECharacterState: uint8 {NORMAL,STUNNED,DEAD,INTERACTABLE,READTEXT}; 
UCLASS()
class BOOK_PROJECT_API AAvatar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAvatar();
	AAvatar(const FObjectInitializer& ObjectInitializer);
	~AAvatar();
	bool inventoryShowing;
	UPROPERTY(BlueprintReadWrite)
		ECharacterState currentState;
	
	UPROPERTY(BlueprintReadWrite)
		ETimeAbility firstPower;
	
	UPROPERTY(BlueprintReadWrite)
		ETimeAbility secondPower;

	UPROPERTY(EditAnywhere,Category = "Map for power cost")
		TMap<FString, float> PowerCost;

	UPROPERTY(EditAnywhere, Category = "Rate of Enenergy loss For Continuous Time Power")
		float delayBetweenDecay;

	bool continuousPowerOn;

	UPROPERTY(EditAnywhere, Category = "Speed for Acceleration ")
		float increasedSpeed;

	UPROPERTY(EditAnywhere, Category = "Air Control Variables")
		float airControlOnBouncePad;

	float originalAirControl;

	float regularWalkingSpeed;

	/*Timer for Handling transport*/
	FTimerHandle testTimer;
	FTimerHandle railTimer;
	FTimerHandle cameraTimer;
	FTimerHandle continuousPowerHandle;
	FVector locationToGoTo;
	float distance;
	float numberOfJumps;
	float numberOfAlternateJumps;
	UPROPERTY(EditAnywhere, Category="Avatar Control Variables")
	float BaseLookRate;
	
	UPROPERTY(EditAnywhere, Category = "Avatar Control Variables")
	float BaseTurnRate;

	UPROPERTY(EditAnywhere, Category = "Avatar Control Variables")
		float JumpHeight;

	UPROPERTY(EditAnywhere, Category = "Avatar Control Variables")
		float highJumpHeight;

	UPROPERTY(EditAnywhere, Category = "Avatar Control Variables")
		float longJumpHeight;
	
	UPROPERTY(EditAnywhere, Category = "Avatar Control Variables")
		float longJumpVelocityXY;

	UPROPERTY(BlueprintReadWrite, Category = "Avatar Control Variables")
		class UCapsuleComponent* capsuleA;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Avatar Animation Variables")
		bool isPunching;

	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category = "Alternate Skeleton")
		class USkeletalMeshComponent* skeleton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grind Variables")
		class UCameraComponent* playerCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grind Variables")
		class USpringArmComponent* cameraBoom;

	UPROPERTY(EditAnywhere, Category = "Warp variable")
		float transitionSpeedCap;

	UPROPERTY(EditAnywhere,BlueprintReadWrite ,Category = "Teleportation effects")
		class UParticleSystemComponent* teleportationParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline declaration")
		class USplineComponent* ourSpline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grind Variables")
		bool isGrinding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grind Variables")
		float percentOfMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grind Variables")
		float timeToGrind;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Avatar Health Variables")
		float currentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Avatar Health Variables")
		float maxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Avatar Energy Variables")
		float currentEnergy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Avatar Energy Variables")
		float maxEnergy;

	UPROPERTY(VisibleAnywhere, Category = "Target for Lock On")
		class ALock_On_Actor* playerTarget;

	UPROPERTY(VisibleAnywhere, Category = "Lock-On properties")
		bool isLockedOn;

	UPROPERTY(BlueprintReadWrite)
		bool isPaused;

	bool isWarping;

	UPROPERTY(BlueprintReadOnly)
		float playTime;

	UPROPERTY(EditAnywhere, Category = "Warp Variables")
		float warpTimeInSeconds;

	UPROPERTY()
		class ACollission_Text* textCollider;
	
	UPROPERTY()
		class AInteractable_Object* interactable;

	UPROPERTY(EditAnywhere, Category = "Debug Testing Category")
		float currentClosestWarpOnScaleFromZeroToOne;

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Punching Colliders")
		class USphereComponent* rightHandSphere;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Punching Colliders")
		class USphereComponent* leftHandSphere;*/

	bool isCrouching;
	bool isFalling;

	UPROPERTY(VisibleAnywhere, Category = "Falling Time")
		float timeFalling;

	UPROPERTY(EditAnywhere, Category = "Actor to Spawn")
		TArray<TSubclassOf<AActor>> AttackProjectiles;

	UPROPERTY(EditAnywhere, Category = "Knockback from Damage")
		float XYKnockback;

	UPROPERTY(EditAnywhere, Category = "Knockback from Damage")
		float ZKnockback;

	UPROPERTY(BlueprintReadWrite, Category = "Grind Variables")
		float grindLaunchHeight;

	UPROPERTY(BlueprintReadWrite, Category = "Grind Variables")
		float grindLaunchDepth;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void Landed(const FHitResult& Hit) override;
	UFUNCTION(BlueprintCallable)
		void Falling() override;

	FVector locationBeforeWarp;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float amount);
	
	void MoveRight(float amount);
	
	void ToggleInventory();
	
	void TurnAtRate(float Rate);
	
	void LookUpAtRate(float Rate);
	
	void Jump();
	
	
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	UFUNCTION(BlueprintCallable)
		void spawnPunchingProjectile();
	
	void startPunching();
	
	void stopPunching();

	void startCrouching();

	void stopCrouching();

	void repeatCrouching();

	void resetTimer();

	UFUNCTION(BlueprintImplementableEvent)  // making use of macro for implementing a method in Blueprints
		void enableAndDisableCollision();

	void lerpToDestination();
	void transition();

	UFUNCTION(BlueprintCallable)
	void beginGrind();
	void grind();

	UFUNCTION(BlueprintImplementableEvent)
		void callWheelChange();

	UFUNCTION(BlueprintImplementableEvent)
		void callEnergyBarChange();

	void MinusHealth(float damageTaken);

	void startDeathSequence();

	UFUNCTION(BlueprintImplementableEvent)
		void playDeathFade();

	UFUNCTION(BlueprintCallable)
		void ResetPlayer();

	void MinusEnergy();

	UFUNCTION()
		void Collision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintImplementableEvent)  // making use of macro for implementing a method in Blueprints
		void showCollectables();

	UFUNCTION(BlueprintImplementableEvent)  // making use of macro for implementing a method in Blueprints
		void changeTimePowers();

	UFUNCTION()
		void setLockOnTarget(class ALock_On_Actor* target);

	UFUNCTION()
		void removeLockOnTarget();

	UFUNCTION()
		void activateLockOnFunction();

	UFUNCTION()
		void lockCameraToTarget();

	UFUNCTION()
		void LeftTimePower();
	UFUNCTION()
		void RightTimePower();
	UFUNCTION()
		void useTimePower(ETimeAbility ability);

	UFUNCTION()
		void subtractEnergyCost();

	UFUNCTION()
		void shutOffContinuousTimePower();

	UFUNCTION()
		void changeToBouncePadAirControl();
	
	UFUNCTION(BlueprintImplementableEvent)
		void changeToWarpMaterial();

	UFUNCTION(BlueprintImplementableEvent)
		void changeToAccelMaterial();

	UFUNCTION(BlueprintImplementableEvent)
		void changeToEnergyMaterial();

	UFUNCTION(BlueprintImplementableEvent)
		void changeToNormalMaterial();

	void addKnockback(FRotator rotationOfHarmfulObject);

	UFUNCTION(BlueprintImplementableEvent)
		void activatePlayerActionSound(int indexOfSound);

	UFUNCTION(BlueprintImplementableEvent)
		void activateGrindSound();
	
	UFUNCTION(BlueprintImplementableEvent)
		void deactivateGrindSound();

	UFUNCTION(BlueprintImplementableEvent)
		void activateSoundFromDestroyedActor(int indexOfSound);
};
