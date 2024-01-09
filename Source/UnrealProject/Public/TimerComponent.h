// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJECT_API UTimerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTimerComponent();

private:
	bool bStarted;
	bool bIsDecreasingTime;
	float FCurrentTimer;

	UPROPERTY(EditAnywhere)
	float FTime;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool HasFinished();

	UFUNCTION(BlueprintCallable,BlueprintPure)
	float GetPercentageTimer();

	UFUNCTION(BlueprintCallable, Category = "Events")
	void ResetTimer();

	UFUNCTION(BlueprintCallable, Category = "Events")
	void IncreasingTimer();

	UFUNCTION(BlueprintCallable, Category = "Events")
	void DecreasingTimer();

	UFUNCTION(BlueprintCallable, Category = "Events")
	void StartTimer();

	UFUNCTION()
	void SetTimer(float time);
	UFUNCTION()
	bool GetHasStarted() const;
};
