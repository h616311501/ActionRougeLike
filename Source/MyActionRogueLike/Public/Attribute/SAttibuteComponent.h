// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttibuteComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYACTIONROGUELIKE_API USAttibuteComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USAttibuteComponent();
	UFUNCTION(BlueprintCallable, Category="Attribute")
	bool ApplyHealthChange(float Delta);
protected:
	// Called when the game starts
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly , Category="Attribute")
	float Health;


public:	


		
};
