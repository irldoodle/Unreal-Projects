// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "ToonTanksPlayerController.h"

ATank::ATank() {
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(BaseMesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("RotateTurret"), this, &ATank::RotateTurret);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
	PlayerInputComponent->BindAction(TEXT("MouseRightClick"), IE_Pressed, this, &ATank::OnMouseRightClick);
}

void ATank::Move(float value) {
	float XValue = value, YValue = value;
	FVector DeltaLocation = TargetLocation - GetActorLocation();

	DeltaLocation.Z = 0;
	DeltaLocation.Normalize();

	Turn(0.1f);

	this->SetActorLocation(GetActorLocation() + DeltaLocation);

	if (FVector::Dist(GetActorLocation(), TargetLocation) < 10.0f)
		bShouldMove = false;
}

void ATank::Turn(float value) {
	FVector ToTarget = TargetLocation - ABasePawn::BaseMesh->GetComponentLocation();

	FRotator LookAtRotation = value * turnRate * FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);

	ABasePawn::BaseMesh->SetWorldRotation(FMath::RInterpTo(
		ABasePawn::BaseMesh->GetComponentRotation(),
		LookAtRotation,
		UGameplayStatics::GetWorldDeltaSeconds(this),
		5.f));

	SpringArm->SetWorldRotation(FMath::RInterpTo(
		ABasePawn::BaseMesh->GetComponentRotation(),
		LookAtRotation,
		UGameplayStatics::GetWorldDeltaSeconds(this),
		5.f));
}

void ATank::BeginPlay() {

	Super::BeginPlay();

	PlayerControlRef = Cast<APlayerController>(GetController());
}

void ATank::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	if (PlayerControlRef) {
		PlayerControlRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

		if (bShouldMove)
			Move(1.0f);
	}

	

}

void ATank::HandleInstantiate() {
	Super::HandleInstanstiate()
}

void ATank::HandleDestruction() {
	//Todo: Add Visual/Sound Effects

	Super::HandleDestruction();

	
}

void ATank::HandleClick(FVector ClickLocation) {
	DrawDebugPoint(GetWorld(),
		//Camera->GetForwardVector(),
		HitResult.ImpactPoint, 10.f,
		FColor(255, 0, 0, 255), true);
	bShouldMove = true;
	TargetLocation = ClickLocation;
}

void ATank::OnMouseRightClick() {
	HandleClick(HitResult.ImpactPoint);
}

void ATank::RotateTurret(float value) {
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = value * turnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	TurretMesh->AddLocalRotation(DeltaRotation);
}