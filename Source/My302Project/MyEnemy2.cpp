// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy2.h"
#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyEnemy2::AMyEnemy2()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FullHealth = 10000;
	//currentHealth = FullHealth;
	
	skeletalMesh =CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	skeletalMesh->SetupAttachment(RootComponent);
	skeletalMesh->SetCollisionProfileName("PhysicsActor");
	skeletalMesh->SetSimulatePhysics(true);
	skeletalMesh->SetGenerateOverlapEvents(true);
	skeletalMesh->SetMobility(EComponentMobility::Movable);
	
	SphereComponent =CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetCollisionProfileName("PhysicsActor");
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSimulatePhysics(true);
	SphereComponent->SetSphereRadius(100);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&AMyEnemy2::OnOverlapBegin);
	

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
	
	// TArray<FHitResult> HitArray;
	//
	// const FVector Start = SphereMesh->GetComponentLocation();
	// const FVector End = Start;
 //    
	// const FCollisionShape SphereShape = FCollisionShape::MakeSphere(Radius);
	//
	// const bool bSweepHit = GetWorld()->SweepMultiByChannel(HitArray,Start,End,FQuat::Identity,ECC_WorldStatic, SphereShape);
	// DrawDebugSphere(GetWorld(),Start,Radius,50,FColor::Orange, true);
 //
	// if(bSweepHit)
	// {
	// 	for(const FHitResult HitResult : HitArray)
	// 	{
	// 		USphereComponent* SphereMesh2 = Cast<USphereComponent>((HitResult.GetActor())->GetRootComponent());
	// 		if(SphereMesh2)
	// 		{
	// 			GEngine->AddOnScreenDebugMessage(6, 10.0f, FColor::Red, FString::Printf(TEXT("bSweepHit")));
	// 			SphereMesh2->AddRadialImpulse(Start, Radius, Strength, RIF_Constant, true);
	// 			
	// 		}
	// 	}
	// }
	
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		FullHealth -= Damage;
		//OtherComp->AddImpulseAtLocation(GetVelocity() * 111111111100.0f, GetActorLocation());
		if( FullHealth <= 0)
		{
			//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathEffect, GetActorLocation() -FVector(0,0,-20), FRotator::ZeroRotator, true);
			Destroy();
		}
      
	}
	
	GEngine->AddOnScreenDebugMessage(3, .10f, FColor::Red, FString::Printf(TEXT("HEALTH: %f"),FullHealth ));
}

void AMyEnemy2::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	
	

	
	
}

