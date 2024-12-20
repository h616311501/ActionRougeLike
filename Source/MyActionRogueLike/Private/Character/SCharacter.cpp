// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedPlayerInput.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

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

	InteractionComponent = CreateDefaultSubobject<USInteractionComponent>("InteractionComponent");
	AttibuteComponent = CreateDefaultSubobject<USAttibuteComponent>("AttibuteComponent");
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if(PlayerController==nullptr)
	{
		return;
	}
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
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
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent && MoveAction && LookAction && AttackAction)
	{
		//绑定移动
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered,this,&ASCharacter::Move);
		//绑定视角旋转
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASCharacter::Look);
		//绑定按下鼠标左键攻击
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ASCharacter::Attack);
		//绑定按下跳跃
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ASCharacter::Jump);
		
	}
}

void ASCharacter::Move(const FInputActionValue& Value)
{
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
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}

void ASCharacter::Attack(const FInputActionValue& Value)
{
	if(ProjectileClass==nullptr)
	{
		return;
	}
	if (InteractionComponent)
	{
		InteractionComponent->PrimaryInteract();
	}
	PlayAnimMontage(AttackMontage);
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttck,this,&ASCharacter::PrimaryAttck_TimerHandle,0.2f);
	//获取屏幕中间的方向，让角色旋转向屏幕的中心方向
	FRotator ActorLookRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),GetOwner()->GetActorLocation());
	GetMesh()->SetWorldRotation(ActorLookRotator);
}

void ASCharacter::PrimaryAttck_TimerHandle()
{
	if (ensure(ProjectileClass))
	{
		UE_LOG(LogTemp,Warning,TEXT("AttackAction"));
		//生成位置
		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
		FTransform SpawnTransform = FTransform(GetControlRotation(),HandLocation);
		//生成碰撞规则
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;
		GetWorld()->SpawnActor<AActor>(ProjectileClass,SpawnTransform,SpawnParams);
	}

}
