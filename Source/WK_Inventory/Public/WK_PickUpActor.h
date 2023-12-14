// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "InventoryComponent.h"

#include "WK_PickUpActor.generated.h"

UCLASS()
class WK_INVENTORY_API AWK_PickUpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWK_PickUpActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item info")
	int ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item info")
	int ItemAmount;


	//Data
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	class UDataTable* ItemBase;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
