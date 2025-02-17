// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UPROPERTY(EditDefaultsOnly, Category = "Combat") UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(VisibleAnywhere, Category = "Movement") class UProjectileMovementComponent* ProjectileMovementComponent;

	UFUNCTION() void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* Othercomp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere) float Damage = 50.f;

	UPROPERTY(EditAnywhere, Category = "Combat") class UParticleSystem* HitParticles;
	UPROPERTY(VisibleAnywhere, Category = "Combat") class UParticleSystemComponent* TrailParticles;

};
