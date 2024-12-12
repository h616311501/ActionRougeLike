// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedPlayerInput.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	bUseControllerRotationYaw = false;
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
	if (EnhancedInputComponent && MoveAction && LookAction && MyAttackAction)
	{
		UE_LOG(LogTemp,Warning,TEXT("MoveAction and LookAction Finish"));
		//绑定移动
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered,this,&ASCharacter::Move);
		//绑定视角旋转
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASCharacter::Look);
		//绑定按下鼠标左键攻击
		EnhancedInputComponent->BindAction(MyAttackAction, ETriggerEvent::Triggered, this, &ASCharacter::AttackAction);
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
		//前后移动
		const FVector ForawrdDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ControlRotation.Vector(),MovementVector.Y);
		//左右移动
		const FVector RightDirection = FRotationMatrix(ControlRotation).GetScaledAxis(EAxis::Y);
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

void ASCharacter::AttackAction(const FInputActionValue& Value)
{
	if(ProjectileClass==nullptr)
	{
		return;
	}
	
	bool BoolValue = Value.Get<bool>();
	UE_LOG(LogTemp,Warning,TEXT("AttackAction"));
	//生成位置
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	FTransform SpawnTransform = FTransform(GetControlRotation(),HandLocation);
	//生成碰撞规则
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<AActor>(ProjectileClass,SpawnTransform,SpawnParams);
}
