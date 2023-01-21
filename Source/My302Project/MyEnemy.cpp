// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy.h"
#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/EngineTypes.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AMyEnemy::AMyEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	SphereComponent =CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetCollisionProfileName("Pawn");
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSimulatePhysics(false);
	SphereComponent->SetSphereRadius(100);
	SphereComponent->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&AMyEnemy::OnOverlapBegin);
	SphereComponent->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("Explosion"));

}

// Called when the game starts or when spawned
void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		
      	GEngine->AddOnScreenDebugMessage(9, .18f, FColor::Red, FString::Printf(TEXT("HEALTH: %f")));
	}
	


	
}


// Called to bind functionality to input
void AMyEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



