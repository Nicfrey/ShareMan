// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageableInterface.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJECT_API UHealthComponent : public UActorComponent, public IDamageableInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int MaxHealth;
	// Sets default values for this component's properties
	UHealthComponent();
private:
	bool bIsAlive;
	int M_Health;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;
	UFUNCTION(BlueprintCallable)
	bool IsOutOfLife() const;
	UFUNCTION(BlueprintCallable)
	void Revive();
	UFUNCTION(BlueprintCallable)
	void Die();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);
	UPROPERTY(BlueprintAssignable)
	FOnDeathSignature OnDeath;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameOverSignature);
	UPROPERTY(BlueprintAssignable)
	FOnGameOverSignature OnGameOver;

	virtual void DoDamage_Implementation() override;
};
