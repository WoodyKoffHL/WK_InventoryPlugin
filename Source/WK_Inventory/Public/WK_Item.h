// Woodykoff production. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryComponent.h"

#include "WK_Item.generated.h"

UCLASS()
class WK_INVENTORY_API AWK_Item : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWK_Item();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Using Item")
	bool canUse = true;

	UFUNCTION(BlueprintCallable, Category = "Using Item")
	void UseThisItem(AActor* OwnerActor, int ItemID, int ItemAmount);

	UFUNCTION(BlueprintCallable, Category = "Using Item")
	bool CanUseThisItem(AActor* OwnerActor, int ItemID, int ItemAmount);

	UFUNCTION(BlueprintImplementableEvent)
	void CheckCanUsingEvent(AActor* OwnerActor, int ItemID, int ItemAmount);

	UFUNCTION(BlueprintImplementableEvent)
	void CallUsingItem(AActor* OwnerActor, int ItemID, int ItemAmount);



};
