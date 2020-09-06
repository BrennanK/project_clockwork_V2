// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"
UENUM() enum class EProjectileType{Standard,Tracking};
UCLASS()
class BOOK_PROJECT_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	AProjectile(const FObjectInitializer &ObjectInitializer);
	~AProjectile();
	UPROPERTY(EditAnywhere, Category = "Projectile Variables")
		float callSpeed;

	UPROPERTY(EditAnywhere, Category = "Projectile Variables")
		float amountToMove;

	FTimerHandle moveTimer;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="State Of Projectile")
		EProjectileType typeOfProjectile;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Variables")
		class USphereComponent* projectileCollider;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Variables")
		class UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, Category = "Projectile Variables")
		float damage;

	class AAvatar* player;

	UPROPERTY(EditAnywhere, Category = "Projectile Variables")
		float speed;

	UPROPERTY(EditAnywhere, Category = "Projectile Variables")
		float lifeTime;

	float life;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void moveForward();
	UFUNCTION()
		void Collision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
