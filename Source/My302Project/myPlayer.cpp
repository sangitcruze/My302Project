// Fill out your copyright notice in the Description page of Project Settings.
//Shangit cruze 

#include "myPlayer.h"

#include "MyEnemy2.h"
#include "MyEnemy.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"

// AmyPlayerCharacter

AmyPlayer::AmyPlayer()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
    Stamina = 10;
	// set our turn rate for input
	TurnRateGamepad = 50.f;
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("Explosion"));
	RadialForceComponent->SetupAttachment(RootComponent);
	RadialForceComponent->Radius = 100;
	SphereComponent =CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RadialForceComponent);
	SphereComponent->SetSimulatePhysics(false);

    SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&AmyPlayer::OnOverlapBegin);
	SphereComponent->SetSphereRadius(100);
	SphereComponent->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
    
	
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AmyPlayer::Tick(float DeltaTime)
{
	// this is required or it crashes
	Super::Tick(DeltaTime);
	// whatever functions after here should pass in delta time if needed
	UpdateDash(DeltaTime);
}

void AmyPlayer::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AmyPlayer::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}

	
}






void AmyPlayer::Dash()
{
	Toggle_Dash = true;
	Dash_Pressed = true;
	
		GetCharacterMovement()->MaxWalkSpeed = 5000.0f;
		GetCharacterMovement()->MaxAcceleration = 5000.0f;
		GetCharacterMovement()->BrakingFriction = 2000.0f;
	
	
	
}




void AmyPlayer::StopDash()
{
	Toggle_Dash = false;
	Dash_Pressed = false;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MaxAcceleration = 2400.0f;
	GetCharacterMovement()->Velocity.X = 2400.f;
	GetCharacterMovement()->Velocity.Y = 2400.f;
	
}

void AmyPlayer::UpdateDash(float deltaTime)
{
	
		if (Toggle_Dash == true)
		{
			dashTimer += deltaTime;
			
				if(Dash_Pressed == true)
				{
					Stamina -= dashTimer;
					if(Stamina<=0)
					{
					StopDash();
					Dash_Pressed = false;
					}
					
				dashTimer = 0;
		   	
			}
		}
	
	
}

void AmyPlayer::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if ((OtherActor != nullptr) &&(OtherActor!= this) && (OtherComp != nullptr))
	{
		if(OtherActor->Tags.Contains("Coin"))
		{
			Stamina += 2;
			
			GEngine->AddOnScreenDebugMessage(8, 2.10f, FColor::Red, FString::Printf(TEXT("picked up coin ")));
			OtherActor->Destroy();
			return;
		}
		
		
	    
         
		 AMyEnemy2* Enemy = Cast<AMyEnemy2>(OtherActor);
	
		 if(Enemy!=nullptr)
		 {
		 	
     	 	
		 	 Enemy->GetMesh()->SetSimulatePhysics(true);
		 	 FVector Direction = this->GetActorLocation() - Enemy->GetActorLocation();
		 	 Direction.Normalize();
		 	 float Scale = 9090900;
            
		 	Enemy->GetMesh()->AddForce(-Direction* Scale + FVector(0,0,9000000));
		 
		 }
		
	}
	
}




//////////////////////////////////////////////////////////////////////////
// Input

void AmyPlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	//InputComponent->BindAction("Dash", IE_Released, this, &AmyPlayer::Dash);
	PlayerInputComponent->BindAction("Dash",IE_Released,this,&AmyPlayer::StopDash);
	PlayerInputComponent->BindAction("Dash",IE_Pressed,this,&AmyPlayer::Dash);
	
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AmyPlayer::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AmyPlayer::MoveRight);



	

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &AmyPlayer::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &AmyPlayer::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AmyPlayer::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AmyPlayer::TouchStopped);
}

void AmyPlayer::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AmyPlayer::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

//void AmyPlayer::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
//{
	//Dash();
//}

void AmyPlayer::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AmyPlayer::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}







	
	


