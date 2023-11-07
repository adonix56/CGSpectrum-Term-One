// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireDamageActor.generated.h"

class UDealDamageComponent;
class UParticleSystemComponent;

UCLASS()
class TERMONE_API AFireDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireDamageActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//APawn* PlayerPawn;

	UPROPERTY(EditAnywhere, NoClear)
	UDealDamageComponent* DealDamageComponent;

	UPROPERTY(EditAnywhere, NoClear)
	UParticleSystemComponent* ParticleSystemComponent;

	UPROPERTY(EditAnywhere)
	float ToggleTime = 5.0f;

	float CurrentTimer = 0.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
