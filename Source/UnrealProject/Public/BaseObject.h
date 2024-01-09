// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimerComponent.h"
#include "GameFramework/Actor.h"
#include "BaseObject.generated.h"

DECLARE_EVENT(ABaseObject, FOnVelocityTooHigh)

UCLASS()
class UNREALPROJECT_API ABaseObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseObject();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTimerComponent* TimerComponent;

	UPROPERTY(BlueprintReadOnly)
	UTimerComponent* TimerBeforeVelocityCheck;
	
private:
	UPROPERTY(EditAnywhere)
	int MaxVelocityBeforeDamage{150};
	bool bLastHitIsPlayer;

	FVector CurrentVelocity;

	FTimerHandle DelayHandle;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnVelocityTooHigh);
	UPROPERTY(BlueprintAssignable)
	FOnVelocityTooHigh OnVelocityTooHigh;

	UFUNCTION()
	void CheckIfObjectMoves();
};
