// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedPlayerInput.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if(PlayerController==nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("PlayerController==nullptr"));
		return;
	}
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	UE_LOG(LogTemp,Warning,TEXT("EnhancedInputSystem Finish"));
	if (EnhancedInputSystem && DefaultMappingContext)
	{
		EnhancedInputSystem->AddMappingContext(DefaultMappingContext,0);
	}
}



// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UE_LOG(LogTemp,Warning,TEXT("SetupPlayerInputComponent Finish"));
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent && MoveAction && LookAction)
	{
		UE_LOG(LogTemp,Warning,TEXT("MoveAction and LookAction Finish"));
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered,this,&ASCharacter::Move);
		
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASCharacter::Look);
 
	}
}

void ASCharacter::Move(const FInputActionValue& Value)
{
	UE_LOG(LogTemp,Warning,TEXT("Move Value : %f"),Value);
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller)
	{
		const FRotator ControlRotation = Controller->GetControlRotation();
		const FRotator YawRotation = FRotator(0.0f,ControlRotation.Yaw,0.0f);
 
		const FVector ForawrdDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
 
		AddMovementInput(ForawrdDirection,MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ASCharacter::Look(const FInputActionValue& Value)
{

	FVector2D LookVector = Value.Get<FVector2D>();
	if (Controller)
	{
		UE_LOG(LogTemp,Warning,TEXT("Look Value X : %f"),LookVector.X);
		UE_LOG(LogTemp,Warning,TEXT("Look Value Y : %f"),LookVector.Y);
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}