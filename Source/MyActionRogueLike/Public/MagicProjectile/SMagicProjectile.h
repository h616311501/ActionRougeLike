// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "SMagicProjectile.generated.h"

UCLASS()
class MYACTIONROGUELIKE_API ASMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASMagicProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Projectile")
	UShapeComponent* shapeComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Projectile")
	UProjectileMovementComponent* movementComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Projectile")
	UParticleSystemComponent* effectComp;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
