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
	int ItemAmount = PickActor->ItemAmount;
	FName RowName = ItemBase->GetRowNames()[0];
	FItemsData* ItemRow = ItemBase->FindRow<FItemsData>(RowName, ItemName);
	if (!ItemRow) return;
	int FoundedSlotIndex = -1;
	if (UseStacks || ItemRow->itemInfo.Stackeble) {
		int MaxStack = ItemRow->itemInfo.MaxStack;
		// Search Slot
		FoundedSlotIndex = SearhSlotForStack(ItemID, MaxStack);
		if (FoundedSlotIndex == -1) {
			FoundedSlotIndex = SearchEmptySlot();
		}
		if (FoundedSlotIndex == -1) return;
		if (!InventorySlots.IsValidIndex(FoundedSlotIndex)) return;

		FItemSlot FoundedSlot = InventorySlots[FoundedSlotIndex];
		int totalAmount = FoundedSlot.Amount + ItemAmount;
		if (totalAmount > MaxStack) {
			int rest = totalAmount - MaxStack;
			AddItem(PickActor, ItemID, MaxStack);
			if (rest > MaxStack) {
				while (rest > MaxStack) {
					AddItem(PickActor, ItemID, MaxStack);
					rest = rest - MaxStack;
				}
				AddItem(PickActor, ItemID, rest);
				PickActor->Destroy();
			}
			else {
				AddItem(PickActor, ItemID, rest);
				PickActor->Destroy();
			}
			
		}
		else {
			InventorySlots[FoundedSlotIndex].Amount = totalAmount;
			InventorySlots[FoundedSlotIndex].ID = ItemID;
			PickActor->Destroy();
		}
	}
	else {
		FoundedSlotIndex = SearchEmptySlot();
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
		if (InventorySlots[i].ID == it_id || InventorySlots[i].Amount < it_maxStack ) {
			return i;
		}
	}
	return -1;
}

int UInventoryComponent::SearchEmptySlot()
{
	for (int i = 0; i <= InventorySlots.Num(); i++) {
		if (InventorySlots[i].ID == -1) return i;
	}
	return -1;
}

#pragma endregion