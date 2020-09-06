// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class BOOK_PROJECT_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();
	AEnemyCharacter(const FObjectInitializer &ObjectInitializer);
	~AEnemyCharacter();
	UPROPERTY(EditAnywhere, Category = "Behavior")
		class UBehaviorTree *BotBehavior;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeleton for Visuals")
		class USkeletalMeshComponent* skeleton;

	UPROPERTY(BlueprintReadWrite, Category = "Capsule for Collision")
		class UCapsuleComponent* capsuleCollider;

	UPROPERTY(EditAnywhere, Category = "Speed of Movement")
		float movementSpeed;

	UPROPERTY(EditAnywhere, Category = "Delay of Death")
		float delay;

	FTimerHandle destructionHandler;

	UPROPERTY(EditAnywhere, Category = "Knockback Variables")
		float XYKnockback;

	UPROPERTY(EditANywhere, Category = "Knockback Variables")
		float ZKnockback;

	UPROPERTY(VisibleAnywhere, Category = "Respawn Variables")
		float delayOfRespawn;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Respawn Variables")
		bool isRespawnable;

	class AEnemy_Spawner* spawnerRef;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void initiateDestruction(FRotator projectileRotation);

	UFUNCTION()
	virtual void DestroyThisUnit();

	UFUNCTION()
	virtual	void Die();
};
