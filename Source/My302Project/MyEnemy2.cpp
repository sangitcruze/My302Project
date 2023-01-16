// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy2.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyEnemy2::AMyEnemy2()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = 1000;
	
	skeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	skeletalMesh->SetupAttachment(RootComponent);
	skeletalMesh->SetCollisionProfileName("PhysicsActor");
	skeletalMesh->SetSimulatePhysics(false);
	skeletalMesh->SetGenerateOverlapEvents(true);
	skeletalMesh->SetMobility(EComponentMobility::Movable);
    
}

// Called when the game starts or when spawned
void AMyEnemy2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyEnemy2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyEnemy2::EnemyTakeDamage(float damage)
{
	Health -= damage;

	if( currentHealth <= 0)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),P_Fire, GetActorLocation(), true);
		DestroyEnemyActor();
	}
}

void AMyEnemy2::DestroyEnemyActor()
{
	this->Destroy();
}



// Called to bind functionality to input
void AMyEnemy2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

