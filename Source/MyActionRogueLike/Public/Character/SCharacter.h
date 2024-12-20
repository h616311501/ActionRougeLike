// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Attribute/SAttibuteComponent.h"
#include "Camera/CameraComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "InteractionComponent/SInteractionComponent.h"
#include "SCharacter.generated.h"

class UInputMappingContext;
UCLASS()
class MYACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Attack(const FInputActionValue& Value);
	
	UPROPERTY(VisibleAnywhere,Category="SCharacter")
	USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere,Category="SCharacter")
	UCameraComponent* CameraComponent;
	
	UPROPERTY(EditAnywhere,Category="Attack")
	TSubclassOf<AActor> ProjectileClass;//TSubclassOf 只显示寻找类以及子类
	
	UPROPERTY(EditAnywhere,Category="Attack")
	UAnimMontage* AttackMontage;

	FTimerHandle TimerHandle_PrimaryAttck;

	void PrimaryAttck_TimerHandle();
	//射线组件，Debug用
	UPROPERTY(EditAnywhere,Category="SCharacter")
	USInteractionComponent* InteractionComponent;
	//角色属性，血量，蓝量等
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="SCharacter")
	USAttibuteComponent* AttibuteComponent;
	//输入映射
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	//移动
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;
	//上下左右看
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;
private:


};


