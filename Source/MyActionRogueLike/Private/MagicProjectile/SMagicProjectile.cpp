// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicProjectile/SMagicProjectile.h"

#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	shapeComp = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	RootComponent = shapeComp;
	/*shapeComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	shapeComp->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);*/
	shapeComp->SetCollisionProfileName("Projectile");
	
	effectComp = CreateDefaultSubobject<UParticleSystemComponent>("StaticMeshComponent");
	effectComp->SetupAttachment(shapeComp);
	
	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	movementComp->InitialSpeed = 1000.0f;
	movementComp->bRotationFollowsVelocity = true;
	movementComp->bInitialVelocityInLocalSpace = true;

	

	

	
}

// Called when the game starts or when spawned
void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

