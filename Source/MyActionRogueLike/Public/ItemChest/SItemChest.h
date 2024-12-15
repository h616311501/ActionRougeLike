// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/SInterface.h"
#include "SItemChest.generated.h"

UCLASS()
class MYACTIONROGUELIKE_API ASItemChest : public AActor , public ISInterface
{
	GENERATED_BODY()
	
	void Interact_Implementation(APawn* Pawn);
public:	
	// Sets default values for this actor's properties
	ASItemChest();
	UPROPERTY(EditAnywhere)
	float TargetPitch;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMesh;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
