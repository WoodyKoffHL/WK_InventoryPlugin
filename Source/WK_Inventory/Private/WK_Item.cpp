// Woodykoff production. All rights reserved.


#include "WK_Item.h"
#include "InventoryComponent.h"


// Sets default values
AWK_Item::AWK_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWK_Item::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWK_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWK_Item::UseThisItem(AActor* OwnerActor, int ItemID, int ItemAmount)
{
	if (CanUseThisItem(OwnerActor, ItemID, ItemAmount)) {
		CallUsingItem(OwnerActor, ItemID, ItemAmount);
		this->Destroy();
	}
	else {
		this->Destroy();
	}
}

bool AWK_Item::CanUseThisItem(AActor* OwnerActor, int ItemID, int ItemAmount)
{
	CheckCanUsingEvent(OwnerActor, ItemID, ItemAmount);
	return canUse;
}


