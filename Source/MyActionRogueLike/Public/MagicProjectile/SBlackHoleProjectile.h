// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "SBlackHoleProjectile.generated.h"

UCLASS()
class MYACTIONROGUELIKE_API ASBlackHoleProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASBlackHoleProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Projectile")
	UShapeComponent* shapeComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Projectile")
	UProjectileMovementComponent* movementComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Projectile")
	UParticleSystemComponent* effectComp;
	
	UPROPERTY(EditAnywhere,Category="Components")
	URadialForceComponent* RadialForceComponent;

	UFUNCTION(BlueprintCallable, Category="Projectile")
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) ;
	
};

inline void ASBlackHoleProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComponent->FireImpulse();
}
