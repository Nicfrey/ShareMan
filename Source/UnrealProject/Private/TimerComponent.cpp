// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerComponent.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UTimerComponent::UTimerComponent(): bStarted{}, bIsDecreasingTime{}, FCurrentTimer{}, FTime{5.f}
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTimerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UE_LOG(LogTemp, Warning, TEXT("Started Tick: %f"), FTime);

}


// Called every frame
void UTimerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if(!bStarted)
	{
		return;
	}

	if(bIsDecreasingTime)
	{
		FCurrentTimer -= DeltaTime;
		if(FCurrentTimer <= 0)
		{
			ResetTimer();
		}
	}
	else
	{
		const float incrementResult{ FCurrentTimer + DeltaTime };
		FCurrentTimer = UKismetMathLibrary::FClamp(incrementResult, 0.f, FTime);
	}
	UE_LOG(LogTemp, Warning, TEXT("FCurrentTimer: %f"), FCurrentTimer);
	UE_LOG(LogTemp, Warning, TEXT("FTime: %f"), FTime);
}

bool UTimerComponent::HasFinished()
{
	return GetPercentageTimer() >= 1.f;
}

float UTimerComponent::GetPercentageTimer()
{
	UE_LOG(LogTemp, Warning, TEXT("FCurrentTimer inside function: %f"), FCurrentTimer);

	const float resultPercentage{ FCurrentTimer / FTime };
	
	UE_LOG(LogTemp, Warning, TEXT("INCREMENT: %f"), resultPercentage);
	return resultPercentage;
}

void UTimerComponent::ResetTimer()
{
	FCurrentTimer = 0.f;
	bStarted = false;
	bIsDecreasingTime = false;
}

void UTimerComponent::IncreasingTimer()
{
	bIsDecreasingTime = false;
}

void UTimerComponent::DecreasingTimer()
{
	bIsDecreasingTime = true;
}

void UTimerComponent::StartTimer()
{
	bStarted = true;
	bIsDecreasingTime = false;
}

void UTimerComponent::SetTimer(float time)
{
	FTime = time;
}

bool UTimerComponent::GetHasStarted() const
{
	return bStarted;
}
