// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseObject.h"

// Sets default values
ABaseObject::ABaseObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualObject"));
	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetupAttachment(RootComponent);
	TimerComponent = CreateDefaultSubobject<UTimerComponent>(TEXT("TimerBeforeTriggerActive"));
	TimerBeforeVelocityCheck = CreateDefaultSubobject<UTimerComponent>(TEXT("TimerBeforeVelocityCheck"));
	TimerBeforeVelocityCheck->SetTimer(0.5f);
	TimerComponent->SetTimer(5.f);
	TimerComponent->StartTimer();
	TimerBeforeVelocityCheck->StartTimer();
}

// Called when the game starts or when spawned
void ABaseObject::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrentVelocity = GetVelocity();
	UE_LOG(LogTemp, Warning, TEXT("Started Tick: %s"), TimerComponent->GetHasStarted() ? TEXT("YES") : TEXT("NO"));
	UE_LOG(LogTemp, Warning, TEXT("TimerBeforeVelocityCheck Tick: %f"), TimerBeforeVelocityCheck->GetPercentageTimer());
	UE_LOG(LogTemp, Warning, TEXT("TimerComponent Tick: %f"), TimerComponent->GetPercentageTimer());

	if(TimerComponent->HasFinished())
	{
		if (TimerBeforeVelocityCheck->HasFinished())
		{
			UE_LOG(LogTemp, Warning, TEXT("Velocity: %s"), *CurrentVelocity.ToString());
			if (CurrentVelocity.Length() >= MaxVelocityBeforeDamage)
			{
				OnVelocityTooHigh.Broadcast();
			}
			TimerBeforeVelocityCheck->ResetTimer();
			TimerBeforeVelocityCheck->StartTimer();
		}
	}
	
}

void ABaseObject::CheckIfObjectMoves()
{
	if(CurrentVelocity.Length() >= MaxVelocityBeforeDamage)
	{
		OnVelocityTooHigh.Broadcast();
	}
}

