// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include <random>

ATower::ATower() {
	PrimaryActorTick.bCanEverTick = true;

}
void ATower::BeginPlay() {
	Super::BeginPlay();
	
}
void ATower::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	RotateTurret(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
	timer += DeltaTime;
	if (timer >= 1.0f / fireRate) {
		Fire();
		timer = 0;
	}
}
void ATower::Fire() {
	Super::Fire();
}