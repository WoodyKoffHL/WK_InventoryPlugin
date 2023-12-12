// Woodykoff production. All rights reserved.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// Generate EmptySlots
	GenerateSlots();

	// ...
	
}

void UInventoryComponent::GenerateSlots()
{
	InventorySlots.Empty();
	for (int i = 0; i < AmountInventorySlots; i++) {
		FItemSlot NewSlot;
		if (StartInventorySlots.IsValidIndex(i)) {
			NewSlot = StartInventorySlots[i];
		}
		else {
			NewSlot.Amount = 0;
			NewSlot.ID = -1;
		}
		InventorySlots.Add(NewSlot);
	}

	FastSlots.Empty();
	for (int i = 0; i < AmountFastSlots; i++) {
		FItemSlot NewSlot;
		if (StartFastSlots.IsValidIndex(i)) {
			NewSlot = StartFastSlots[i];
		}
		else {
			NewSlot.Amount = 0;
			NewSlot.ID = -1;
		}
		FastSlots.Add(NewSlot);
	}

	EquipSlots.Empty();
	for (int i = 0; i < AmountEquipSlots; i++) {
		FItemSlot NewSlot;
		if (StartEquipSlots.IsValidIndex(i)) {
			NewSlot = StartEquipSlots[i];
		}
		else {
			NewSlot.Amount = 0;
			NewSlot.ID = -1;
		}
		EquipSlots.Add(NewSlot);
	}

	StartInventorySlots.Empty();
	StartFastSlots.Empty();
	StartEquipSlots.Empty();
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

