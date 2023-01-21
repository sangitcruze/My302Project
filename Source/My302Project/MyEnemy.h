// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "myPlayer.h"
#include "CoreMinimal.h"
#include <Components/SkeletalMeshComponent.h>
#include "Materials/Material.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyEnemy.generated.h"

class USphereComponent;
class UAddRadicalImpulse;

UCLASS()

class MY302PROJECT_API AMyEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComponent;
	
	UPROPERTY(EditAnywhere,Category="Forces")
	float Radius = 100.0f;
	UPROPERTY(EditAnywhere, Category="Forces")
	float Strength = 2000000000000000000.0f;
	
	UPROPERTY(EditAnywhere)
	URadialForceComponent* RadialForceComponent;

	// declare overlap begin function
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
     
	// declare overlap end function
	
};

