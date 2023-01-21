// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy2.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/EngineTypes.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyEnemy2::AMyEnemy2()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = 1000000000;
	//currentHealth = FullHealth;
	
	// skeletalMesh =CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	// skeletalMesh->SetupAttachment(RootComponent);
	// skeletalMesh->SetCollisionProfileName("PhysicsActor");
	// skeletalMesh->SetSimulatePhysics(true);
	// skeletalMesh->SetGenerateOverlapEvents(true);
	// skeletalMesh->SetMobility(EComponentMobility::Movable);
	
	SphereComponent =CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetCollisionProfileName("Trigger");
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSimulatePhysics(false);
	SphereComponent->SetSphereRadius(100);
	SphereComponent->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&AMyEnemy2::OnOverlapBegin);
	SphereComponent->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("Explosion"));
   //HealthWidgetComponent->CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	//HealthWidgetComponent->SetupAttachment(RootComponent);
	//HealthWidgetComponent->UObjectInitialized(CreateAbstractDefaultSubobject<>())
	
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

//void AMyEnemy2::EnemyTakeDamage(float damage)
//{
   // float Health =1000;
	//Health -= damage;

	//if( Health <= 0)
	//{
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),P_Fire, GetActorLocation(), true);
		//DestroyEnemyActor();
	//}
//}

//void AMyEnemy2::DestroyEnemyActor()
//{
	//this->Destroy();
//}



// Called to bind functionality to input
void AMyEnemy2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}




void AMyEnemy2::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                               int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	
	
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		
		
		Health -= Damage;
		
	
		if( Health <= 0)
		{
			//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), P_Stun_Stars_Base, GetActorLocation() -FVector(0,0,-20), FRotator::ZeroRotator, true);
			Destroy();
		}
      
	}
	
	GEngine->AddOnScreenDebugMessage(3, .10f, FColor::Red, FString::Printf(TEXT("HEALTH: %f"),Health ));
}

void AMyEnemy2::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	
	

	
	
}

