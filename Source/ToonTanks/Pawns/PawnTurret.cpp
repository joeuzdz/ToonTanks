// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "PawnTank.h"
#include "Kismet/GameplayStatics.h"

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange || !PlayerPawn->GetIsPlayerAlive())
	{
		return;
	}

	RotateTurret(PlayerPawn->GetActorLocation());

}

void APawnTurret::CheckFireCondition()
{

	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("No player pawn found in CheckFireCondition"));
		return;
	}

	if (!PlayerPawn->GetIsPlayerAlive())
	{
		return;
	}

	if (ReturnDistanceToPlayer() <= FireRange)
	{
		Fire();
	}

}

float APawnTurret::ReturnDistanceToPlayer()
{
	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("No player pawn found in ReturnDistanceToPlayer"));
		return -1.f;
	}

	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}



