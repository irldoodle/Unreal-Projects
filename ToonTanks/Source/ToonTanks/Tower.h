// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.h"
#include "Tower.generated.h"


/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	ATower();
	virtual void Tick(float DeltaTime) override; 

protected:
	virtual void BeginPlay() override;
	void Fire();

private:
	UPROPERTY(EditAnywhere, SimpleDisplay, Category = "Combat") float fireRate = 1.0f; //in Rounds Per Second
	float timer = 1.0f;
};
