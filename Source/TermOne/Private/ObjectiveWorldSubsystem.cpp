// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveWorldSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UObjectiveWorldSubsystem::CreateObjectiveWidget(TSubclassOf<UUserWidget> ObjectiveWidgetClass) {
	if (ObjectiveWidget == nullptr) {
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		ObjectiveWidget = CreateWidget<UUserWidget>(PlayerController, ObjectiveWidgetClass);
	}
}

void UObjectiveWorldSubsystem::DisplayObjectiveWidget() {
	ensureMsgf(ObjectiveWidget, TEXT("UOBjectiveWorldSubsystem::DisplayObjectiveWidget() ObjectiveWidget is nullptr. Be sure to call CreateObjectiveWidget() first."));
	ObjectiveWidget->AddToViewport();
}

void UObjectiveWorldSubsystem::OnObjectCompleted() {
	DisplayObjectiveWidget();
}

void UObjectiveWorldSubsystem::AddObjective(UObjectiveComponent* ObjectiveComponent) {
	check(ObjectiveComponent);

	size_t PrevSize = Objectives.Num();
	Objectives.AddUnique(ObjectiveComponent);
	if (Objectives.Num() > PrevSize) {
		ObjectiveComponent->OnStateChanged().AddUObject(this, &UObjectiveWorldSubsystem::OnObjectiveStateChanged);
	}
}

void UObjectiveWorldSubsystem::RemoveObjective(UObjectiveComponent* ObjectiveComponent) {
	Objectives.Remove(ObjectiveComponent);
}

FString UObjectiveWorldSubsystem::GetCurrentObjectiveDescription() {
	if (!Objectives.IsValidIndex(0) || Objectives[0]->GetState() == EObjectiveState::OS_Inactive) {
		return TEXT("N/A");
	}

	FString RetObjective = Objectives[0]->GetDescription();
	if (Objectives[0]->GetState() == EObjectiveState::OS_Completed) {
		RetObjective += TEXT(" Completed!");
	}
	return RetObjective;
}

void UObjectiveWorldSubsystem::OnObjectiveStateChanged(UObjectiveComponent* ObjectiveComponent, EObjectiveState ObjectiveState) {
	DisplayObjectiveWidget();
}