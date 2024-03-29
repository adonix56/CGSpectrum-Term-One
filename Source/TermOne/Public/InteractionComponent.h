// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TextRenderComponent.h"
#include "InteractionComponent.generated.h"

class AActor;
class UCapsuleComponent;
class UPrimitiveComponent;
class UTextRenderComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionSuccess);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TERMONE_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponent();

	//Broadcasted from children
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractionSuccess InteractionSuccess;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UCapsuleComponent* GetTriggerCapsule() const { return TriggerCapsule; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void InteractionStart();

	UPROPERTY(EditAnywhere)
	FText InteractionPrompt;

	UPROPERTY(EditAnywhere, NoClear)
	UCapsuleComponent* TriggerCapsule = nullptr;

	UPROPERTY(EditAnywhere, NoClear)
	UTextRenderComponent* TextRenderComponent = nullptr;

	AActor* InteractingActor = nullptr;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
