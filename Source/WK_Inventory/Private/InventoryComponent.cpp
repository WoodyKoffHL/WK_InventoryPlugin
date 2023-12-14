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

// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

#pragma region BlueprintFunctions

void UInventoryComponent::AddItem(AWK_PickUpActor* PickActor, int ID, int Amount)
{
	

	int ItemID = PickActor->ItemID;
	FString ItemName = FString::FromInt(ItemID);
	int LocalItemAmount = PickActor->ItemAmount;
	FItemsData* ItemRow = ItemBase->FindRow<FItemsData>(FName(ItemName), ItemName);
	if (!ItemRow) return;
	
	if (UseStacks) {
		// Settings Stack On
		if (!ItemRow->itemInfo.Stackeble) {
			// Do not Stack Item
			int FoundedSlotIndex = SearchEmptySlot();
			if (FoundedSlotIndex < 0) return;
			InventorySlots[FoundedSlotIndex].Amount = 1;
			InventorySlots[FoundedSlotIndex].ID = ItemID;
			PickActor->Destroy();
			return;
		}
		// If Item Stack
		int MaxStack = ItemRow->itemInfo.MaxStack;
		int StackIndex = SearhSlotForStack(ItemID, MaxStack);
		int NewInvSlot;

		// If dont found to stack slot - search empty slot
		if (StackIndex < 0) {
			StackIndex = SearchEmptySlot();
		}

		if (StackIndex >= 0) {
			// If founded for stack
			FItemSlot StackSlot = InventorySlots[StackIndex];
			int TotalAmount = StackSlot.Amount + Amount;
			// Check total amount with slot
			if (TotalAmount > MaxStack) {
				int rest = TotalAmount;
				InventorySlots[StackIndex].ID = ItemID;
				InventorySlots[StackIndex].Amount = MaxStack;
				rest = TotalAmount - MaxStack;
					// if last slot be stacked
					if (SearchEmptySlot() < 0) {
						PickActor->ItemAmount = rest;
						return;
					}
					while (rest > MaxStack) {
						NewInvSlot = SearchEmptySlot();
						if (!InventorySlots.IsValidIndex(NewInvSlot)) break;
						InventorySlots[NewInvSlot].ID = ItemID;
						InventorySlots[NewInvSlot].Amount = MaxStack;
						rest = TotalAmount - MaxStack;
					}
					if (rest > 0) {
						NewInvSlot = SearchEmptySlot();
						if (NewInvSlot < 0) return;
						InventorySlots[NewInvSlot].ID = ItemID;
						InventorySlots[NewInvSlot].Amount = rest;
					}
					PickActor->Destroy();
			}
			else  {
				InventorySlots[StackIndex].ID = ItemID;
				InventorySlots[StackIndex].Amount = TotalAmount;
				PickActor->Destroy();
			}
		} // If dont find any slot to add - nothing going on
		
	}
	else {
		// Do not Stack in settings
		int FoundedSlotIndex = SearchEmptySlot();
		if (FoundedSlotIndex < 0) return;
		InventorySlots[FoundedSlotIndex].Amount = 1;
		InventorySlots[FoundedSlotIndex].ID = ItemID;
		PickActor->Destroy();
	}	
}

#pragma endregion


#pragma region PrivateFunctions

// Slots Functions
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
		FItemFastSlot NewSlot;
		if (StartFastSlots.IsValidIndex(i)) {
			NewSlot = StartFastSlots[i];
		}
		else {
			NewSlot.Amount = 0;
			NewSlot.ID = -1;
			NewSlot.Active = false;
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

void UInventoryComponent::PreSaveGame()
{
	// For save and load inventory - use start slots
	StartInventorySlots = InventorySlots;
	StartFastSlots = FastSlots;
	StartEquipSlots = EquipSlots;
	InventorySlots.Empty();
	FastSlots.Empty();
	EquipSlots.Empty();
}

int UInventoryComponent::SearhSlotForStack(int it_id, int it_maxStack)
{
	if (it_id == -1 || it_maxStack <= 0) return -1;
	for (int i = 0; i <= InventorySlots.Num(); i++) {
		if (InventorySlots.IsValidIndex(i)) {
			if (InventorySlots[i].ID == it_id) {
				if (InventorySlots[i].Amount == it_maxStack) {
					continue;
				}
				else {
					return i;
				}
			}
		}
	}
	return -1;
}

int UInventoryComponent::SearchEmptySlot()
{
	int ArrayNum = InventorySlots.Num();
	for (int i = 0; i <= 100; i++) {
		if (!InventorySlots.IsValidIndex(i)) return -1;
		if (InventorySlots[i].ID == -1) return i;
	}
	return -1;
}

#pragma endregion