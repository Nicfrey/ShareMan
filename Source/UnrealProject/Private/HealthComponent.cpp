// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	MaxHealth = 3;
	M_Health = MaxHealth;
	bIsAlive = true;
}

bool UHealthComponent::IsAlive() const
{
	return bIsAlive;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UHealthComponent::IsOutOfLife() const
{
	return M_Health <= 0;
}

void UHealthComponent::Revive()
{
	bIsAlive = true;
}

void UHealthComponent::Die()
{
	bIsAlive = false;
}

int UHealthComponent::GetRemainingLife() const
{
	return M_Health;
}

void UHealthComponent::DoDamage_Implementation()
{
	--M_Health;
	Die();
	// Call on death event
	OnDeath.Broadcast();
	if(IsOutOfLife())
	{
		// Call game over
		OnGameOver.Broadcast();
	}
}
