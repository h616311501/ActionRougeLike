// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "SExplodebarrel.generated.h"

UCLASS()
class MYACTIONROGUELIKE_API ASExplodebarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASExplodebarrel();

	UFUNCTION(BlueprintCallable)
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) ;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category="Components")
	UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(EditAnywhere,Category="Components")
	URadialForceComponent *RadialForceComponent;


	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
