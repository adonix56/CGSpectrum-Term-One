// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TermOnePlayerCharacter.generated.h"

class UHealthComponent;
class UParticleSystemComponent;
class UDamageHandlerComponent;

DECLARE_MULTICAST_DELEGATE(FOnInteractionStart);
DECLARE_MULTICAST_DELEGATE(FOnInteractionCancel);

UCLASS()
class TERMONE_API ATermOnePlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATermOnePlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnDeath(bool IsFellOut);

	UFUNCTION()
	void OnDeathTimerFinished();

	UPROPERTY(EditAnywhere)
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere)
	UDamageHandlerComponent* DamageHandlerComponent;

	UPROPERTY(EditAnywhere)
	float TimeRestartLevelAfterDeath = 2.0f;

	FTimerHandle RestartLevelTimerHandle;

	APlayerController* PlayerController;

	UPROPERTY(EditAnywhere, Category="Effects")
	TSubclassOf<UCameraShakeBase> CamShake;

	//Force Feedback
	UPROPERTY(EditAnywhere, Category = "Haptic Feedback")
	float ForceFeedbackIntensity = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Haptic Feedback")
	float ForceFeedbackDuration = 1.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

	void SetOnFire(float BaseDamage, float DamageTotalTime, float TakeDamageInterval);

	UFUNCTION(BlueprintCallable)
	const bool IsAlive() const;

	UFUNCTION(BlueprintCallable)
	const float GetCurrentHealth() const;

	void StartInteraction();

	void StopInteraction();

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ParticleSystemComponent;

	UFUNCTION(BlueprintCallable)
	void HandleItemCollected();

	UFUNCTION(BlueprintImplementableEvent)
	void ItemCollected();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int ItemsCollected = 0;

	FOnInteractionStart OnInteractionStart;
	FOnInteractionCancel OnInteractionCancel;

	UFUNCTION(BlueprintImplementableEvent)
	void DoorOpenInteractionStarted(AActor* InteractableActor);
};
