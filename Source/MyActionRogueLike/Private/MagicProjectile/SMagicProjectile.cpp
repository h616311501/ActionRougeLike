// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicProjectile/SMagicProjectile.h"

#include "Attribute/SAttibuteComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	shapeComp = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	RootComponent = shapeComp;
	shapeComp->OnComponentBeginOverlap.AddDynamic(this,&ASMagicProjectile::OnActorOverlap);
	/*shapeComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	shapeComp->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);*/
	shapeComp->SetCollisionProfileName("Projectile");

	
	effectComp = CreateDefaultSubobject<UParticleSystemComponent>("StaticMeshComponent");
	effectComp->SetupAttachment(shapeComp);
	
	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	movementComp->InitialSpeed = 1000.0f;
	movementComp->bRotationFollowsVelocity = true;
	movementComp->bInitialVelocityInLocalSpace = true;
	movementComp->ProjectileGravityScale = 0;

	

	

	
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

void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp,Warning,TEXT("碰到了%s"), *OtherActor->GetName())
	if (OtherActor)
	{
		UE_LOG(LogTemp,Warning,TEXT("打中了%s"), *OtherActor->GetName())
		//从Actor这个目标上获得到AttibuteComponent这个类
		APawn* myAPawn = Cast<APawn>(OtherActor);
		USAttibuteComponent* AttibuteComponent = Cast<USAttibuteComponent>(myAPawn->GetComponentByClass(USAttibuteComponent::StaticClass()));
		if (AttibuteComponent)
		{
			AttibuteComponent->ApplyHealthChange(-20.0f);
			Destroy();
		}
	}
}
