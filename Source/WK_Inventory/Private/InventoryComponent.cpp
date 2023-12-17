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

bool UInventoryComponent::AddItem(AWK_PickUpActor* PickActor, int ID, int Amount)
{
	

	int ItemID = PickActor->ItemID;
	FString ItemName = FString::FromInt(ItemID);
	int LocalItemAmount = PickActor->ItemAmount;
	FItemsData* ItemRow = ItemBase->FindRow<FItemsData>(FName(ItemName), ItemName);
	if (!ItemRow) return false;
	
	if (UseStacks) {
		// Settings Stack On
		if (!ItemRow->itemInfo.Stackeble) {
			// Do not Stack Item
			int FoundedSlotIndex = SearchEmptySlot();
			if (FoundedSlotIndex < 0) return false;
			InventorySlots[FoundedSlotIndex].Amount = 1;
			InventorySlots[FoundedSlotIndex].ID = ItemID;
			PickActor->Destroy();
			return true;
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
						return true;
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
						if (NewInvSlot < 0) return true;
						InventorySlots[NewInvSlot].ID = ItemID;
						InventorySlots[NewInvSlot].Amount = rest;
					}
					PickActor->Destroy();
			}
			else  {
				InventorySlots[StackIndex].ID = ItemID;
				InventorySlots[StackIndex].Amount = TotalAmount;
				PickActor->Destroy();
				return true;
			}
		} // If dont find any slot to add - nothing going on
		
	}
	else {
		// Do not Stack in settings
		int FoundedSlotIndex = SearchEmptySlot();
		if (FoundedSlotIndex < 0) return false;
		InventorySlots[FoundedSlotIndex].Amount = 1;
		InventorySlots[FoundedSlotIndex].ID = ItemID;
		PickActor->Destroy();
		return true;
	}	
	return false;
}

bool UInventoryComponent::UseItemAtIndex(EWK_SlotsType SlotsType, int SlotIndex, int Amount)
{
	if (InventoryType != EWK_OwnerType::Character) return false;

	// USING FROM INVENTORY SLOTS
	if (SlotsType == EWK_SlotsType::Inventory) {
		if (!InventorySlots.IsValidIndex(SlotIndex)) return false;

		// Initialize variables
		FItemSlot ItemSlot = InventorySlots[SlotIndex];
		FItemInfo ItemInfo = GetItemInfo(ItemSlot.ID);
		FTransform SpawnTransform = GetOwner()->GetActorTransform();
		UWorld* ThisLevel = GetWorld();
		if (!ThisLevel) return false;
		TSubclassOf<AWK_Item> ItemClass = ItemInfo.Item;
		AWK_Item* SpawnItem;

		switch (ItemInfo.itemType)
		{
		// USING TYPE //
		/////////////////////////////////////////////////////////////////////
		case EWK_ItemType::Using:
			if (!ItemInfo.Useble) return false;
			if (Amount > 1) {
				if (Amount > ItemSlot.Amount) {
					// Dont have this items amount
					CantUseEvent(ItemInfo, Amount);
					return false;
				}
			}
			if (Amount < 1) Amount = 1;
			if (!ThisLevel && !ItemClass) return false;
			SpawnItem = ThisLevel->SpawnActor<AWK_Item>(ItemClass, SpawnTransform);
			if (!SpawnItem) return false;
			SpawnItem->UseThisItem(GetOwner(), ItemSlot.ID, Amount);
			UsedItemEvent(ItemInfo, Amount);
			InventorySlots[SlotIndex].Amount = InventorySlots[SlotIndex].Amount - Amount;
			if (InventorySlots[SlotIndex].Amount <= 0) {
				InventorySlots[SlotIndex].Amount = 0;
				InventorySlots[SlotIndex].ID = -1;
			}
			return true;
			break;
		// QUEST ITEM TYPE //
		/////////////////////////////////////////////////////////////////////
		case EWK_ItemType::Quest:
			break;
		}		
	}
	
	// USING IN FAST SLOT
	else if (SlotsType == EWK_SlotsType::Fast){
		// Initialize variables
		FItemFastSlot ItemSlot = FastSlots[SlotIndex];
		FItemInfo ItemInfo = GetItemInfo(ItemSlot.ID);
		FTransform SpawnTransform = GetOwner()->GetActorTransform();
		UWorld* ThisLevel = GetWorld();
		if (!ThisLevel) return false;
		TSubclassOf<AWK_Item> ItemClass = ItemInfo.Item;
		AWK_Item* SpawnItem;

		switch (ItemInfo.itemType)
		{
			// USING TYPE //
			/////////////////////////////////////////////////////////////////////
		case EWK_ItemType::Using:
			if (!ItemInfo.Useble) return false;
			if (Amount > 1) {
				if (Amount > ItemSlot.Amount) {
					// Dont have this items amount
					CantUseEvent(ItemInfo, Amount);
					return false;
				}
			}
			if (Amount < 1) Amount = 1;
			if (!ThisLevel && !ItemClass) return false;
			SpawnItem = ThisLevel->SpawnActor<AWK_Item>(ItemClass, SpawnTransform);
			if (!SpawnItem) return false;
			SpawnItem->UseThisItem(GetOwner(), ItemSlot.ID, Amount);
			UsedItemEvent(ItemInfo, Amount);
			FastSlots[SlotIndex].Amount = FastSlots[SlotIndex].Amount - Amount;
			if (FastSlots[SlotIndex].Amount <= 0) {
				FastSlots[SlotIndex].Amount = 0;
				FastSlots[SlotIndex].ID = -1;
			}
			return true;
			break;
			// QUEST ITEM TYPE //
			/////////////////////////////////////////////////////////////////////
		case EWK_ItemType::Quest:
			break;
		}
	}
	
	// USING IN EQUIP SLOTS
	else if (SlotsType == EWK_SlotsType::Equip) {

	}
	return false;
}

void UInventoryComponent::SetNearItem(AWK_PickUpActor* PickActor, bool Activate)
{
	if (Activate) {
		NearPickActor = PickActor;
	}
	else {
		NearPickActor = nullptr;
	}
}

void UInventoryComponent::UseItemByID(int id, int Amount)
{
	if (InventoryType != EWK_OwnerType::Character) return;


		// Initialize variables
		FItemInfo ItemInfo = GetItemInfo(id);
		FTransform SpawnTransform = GetOwner()->GetActorTransform();
		UWorld* ThisLevel = GetWorld();
		if (!ThisLevel) return;
		TSubclassOf<AWK_Item> ItemClass = ItemInfo.Item;
		AWK_Item* SpawnItem;

		if(ItemInfo.itemType == EWK_ItemType::Using && ItemInfo.itemType == EWK_ItemType::FastUsing &&
			ItemInfo.itemType == EWK_ItemType::Quest) {
			if (Amount < 1) Amount = 1;
			if (!ThisLevel && !ItemClass) return;
			SpawnItem = ThisLevel->SpawnActor<AWK_Item>(ItemClass, SpawnTransform);
			if (!SpawnItem) return;
			SpawnItem->CheckCanUsingEvent(GetOwner(), id, Amount);
			if (SpawnItem->canUse) {
				SpawnItem->UseThisItem(GetOwner(), id, Amount);
				UsedItemEvent(ItemInfo, Amount);
			}
		}
}

void UInventoryComponent::FastUseItemFromPickUp(AWK_PickUpActor* PickActor, int ID, int Amount)
{
	if (InventoryType != EWK_OwnerType::Character) return;


	// Initialize variables
	FItemInfo ItemInfo = GetItemInfo(ID);
	FTransform SpawnTransform = GetOwner()->GetActorTransform();
	UWorld* ThisLevel = GetWorld();
	if (!ThisLevel) return;
	TSubclassOf<AWK_Item> ItemClass = ItemInfo.Item;
	AWK_Item* SpawnItem;

	switch (ItemInfo.itemType)
	{
		// USING TYPE //
		/////////////////////////////////////////////////////////////////////
	case EWK_ItemType::FastUsing:
		if (Amount < 1) Amount = 1;
		if (!ThisLevel && !ItemClass) return;
		SpawnItem = ThisLevel->SpawnActor<AWK_Item>(ItemClass, SpawnTransform);
		if (!SpawnItem) return;
		SpawnItem->CheckCanUsingEvent(GetOwner(), ID, Amount);
		if (SpawnItem->canUse) {
			SpawnItem->UseThisItem(GetOwner(), ID, Amount);
			UsedItemEvent(ItemInfo, Amount);
			PickActor->Destroy();
		}
		break;
	}
}



FItemInfo UInventoryComponent::GetItemInfo(int id)
{
	FItemInfo OutInfo;
	FItemsData* ItemRow = ItemBase->FindRow<FItemsData>(FName(FString::FromInt(id)), FString::FromInt(id));
	if (ItemRow) {
		OutInfo = ItemRow->itemInfo;
	}
	return OutInfo;
}

void UInventoryComponent::SwapItems(int indexIn, int indexOut)
{
	if (!InventorySlots.IsValidIndex(indexIn)) return;
	if (!InventorySlots.IsValidIndex(indexOut)) return;
	FItemSlot Inbound = InventorySlots[indexIn];
	FItemSlot Outbound = InventorySlots[indexOut];
	InventorySlots[indexOut] = Inbound;
	InventorySlots[indexIn] = Outbound;
	return;
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