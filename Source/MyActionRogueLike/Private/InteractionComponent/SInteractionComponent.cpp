// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent/SInteractionComponent.h"

#include "Interface/SInterface.h"

void USInteractionComponent::PrimaryInteract()
{

	FCollisionObjectQueryParams	CollisionObjectQueryParams;
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	AActor* MyOwner = GetOwner();


	FVector Eyelocation;
	FRotator Eyerotation;

	MyOwner->GetActorEyesViewPoint(Eyelocation, Eyerotation);
	
	FVector EndLocation = Eyelocation + (Eyerotation.Vector() * 1000);


	//FHitResult HitResult;
	//bool bBlockHit = GetWorld()->LineTraceSingleByObjectType(HitResult,Eyelocation,EndLocation,CollisionObjectQueryParams);
	TArray<FHitResult> HitResults;
	float Radius = 30.f;
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(Radius);
	bool bBlockHit = GetWorld()->SweepMultiByObjectType(HitResults,Eyelocation,EndLocation,FQuat::Identity,CollisionObjectQueryParams,CollisionShape);
	FColor Color = bBlockHit? FColor::Green : FColor::Red;
	for (FHitResult HitResult : HitResults)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<USInterface>())
			{
				APawn* Pawn = Cast<APawn>(MyOwner);
				ISInterface::Execute_Interact(HitActor,Pawn);
			}
		}

		DrawDebugSphere(GetWorld(),HitResult.ImpactPoint,Radius,10,Color,false,5.0f);

	}
	DrawDebugLine(GetWorld(),Eyelocation,EndLocation,Color,false,5.0f,0,5.0f);
}

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

