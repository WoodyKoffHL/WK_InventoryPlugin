// Woodykoff production. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WK_Interface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWK_Interface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WK_INVENTORY_API IWK_Interface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void CallAddItem(class AWK_PickUpActor* PickActor, int ID, int Amount);
};
