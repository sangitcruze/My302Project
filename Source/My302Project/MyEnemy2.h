// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "myPlayer.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Components/SkeletalMeshComponent.h>
#include "Materials/Material.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyEnemy2.generated.h"

class USphereComponent;


UCLASS()
class MY302PROJECT_API AMyEnemy2 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyEnemy2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FVector GetComponentLocation();
	void AddImpulse();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* skeletalMesh;
	UPROPERTY(EditAnywhere)
	USphereComponent* SphereMesh;
	UPROPERTY(EditAnywhere)
	AmyPlayer* AmyPlayer;
	UPROPERTY(EditAnywhere,Category="Forces")
	float Radius = 500.0f;
	UPROPERTY(EditAnywhere, Category="Forces")
	float Strength = 2000.0f;
	
    // declare overlap begin function
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
   
	float FullHealth;
	float currentHealth;
	float PlayerSpeed = GetCharacterMovement()->MaxWalkSpeed;
    float Damage = PlayerSpeed;
	


};
