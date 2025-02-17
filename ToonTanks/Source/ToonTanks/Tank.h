// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"


/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
public:
	ATank();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;
	APlayerController* GetTankPlayerController() const { return PlayerControlRef; }
	void HandleDestruction();
	void HandleClick(FVector ClickLocation);
protected:
	virtual void BeginPlay() override;
	void OnMouseRightClick();
	void RotateTurret(float value);
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Components") class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Components") class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, Category = "Movement") float speed = 200.f;
	UPROPERTY(EditAnywhere, Category = "Movement") float turnRate = 45.f;
	void Move(float value);
	void Turn(float value);
	bool bShouldMove = false;
	FVector TargetLocation;
	FHitResult HitResult;
	
	APlayerController* PlayerControlRef;
};
