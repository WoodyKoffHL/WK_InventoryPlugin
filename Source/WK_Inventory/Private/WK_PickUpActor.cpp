// Fill out your copyright notice in the Description page of Project Settings.


#include "WK_PickUpActor.h"

// Sets default values
AWK_PickUpActor::AWK_PickUpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWK_PickUpActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWK_PickUpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

