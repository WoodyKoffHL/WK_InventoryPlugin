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

