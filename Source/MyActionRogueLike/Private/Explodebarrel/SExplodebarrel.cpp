// Fill out your copyright notice in the Description page of Project Settings.


#include "Explodebarrel/SExplodebarrel.h"

// Sets default values
ASExplodebarrel::ASExplodebarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("SphereComponent");
	RootComponent = StaticMeshComponent;
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComponent");
	RadialForceComponent->SetupAttachment(StaticMeshComponent);
	RadialForceComponent->Radius = 1000.0f;
	RadialForceComponent->ImpulseStrength = 10000.0f;
	RadialForceComponent->bImpulseVelChange = true;
	

}

void ASExplodebarrel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComponent->FireImpulse();
}

// Called when the game starts or when spawned
void ASExplodebarrel::BeginPlay()
{
	Super::BeginPlay();
	StaticMeshComponent->OnComponentHit.AddDynamic(this, &ASExplodebarrel::OnHit);
}


// Called every frame
void ASExplodebarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

