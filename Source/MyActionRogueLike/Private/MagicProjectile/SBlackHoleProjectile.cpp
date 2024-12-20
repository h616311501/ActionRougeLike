// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicProjectile/SBlackHoleProjectile.h"

#include "Components/SphereComponent.h"


// Sets default values
ASBlackHoleProjectile::ASBlackHoleProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	shapeComp = CreateDefaultSubobject<USphereComponent>("Sphere");
	RootComponent = shapeComp;
	shapeComp->SetCollisionProfileName("Projectile");

	
	effectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComponent");
	effectComp->SetupAttachment(shapeComp);

	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	movementComp->InitialSpeed = 1000.0f;
	movementComp->bRotationFollowsVelocity = true;
	movementComp->bInitialVelocityInLocalSpace = true;
	movementComp->ProjectileGravityScale = 0;
	
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComponent");
	RadialForceComponent->Radius = 1000.0f;
	RadialForceComponent->ImpulseStrength = -10000.0f;
	RadialForceComponent->bImpulseVelChange = true;
}

// Called when the game starts or when spawned
void ASBlackHoleProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASBlackHoleProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

