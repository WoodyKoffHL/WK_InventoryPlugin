// Woodykoff production. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
// WK
#include "WK_Inventory.h"
#include "WK_Item.h"
#include "WK_PickUpActor.h"
// Data Base
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
// Generate
#include "InventoryComponent.generated.h"

UENUM(BlueprintType)
enum class EWK_OwnerType : uint8 {
	Character UMETA(DisplayName = "Character Inventory"),
	Chest      UMETA(DisplayName = "chest (box)"),
	Bake     UMETA(DisplayName = "furnace Bake"),
	Workbench     UMETA(DisplayName = "Workbench box"),
	Enemy     UMETA(DisplayName = "Enemy loot"),
	Shop     UMETA(DisplayName = "Shop or NPC"),
};

UENUM(BlueprintType)
enum class EWK_ItemType : uint8 {
	Quest        UMETA(DisplayName = "For Quest"),
	Using        UMETA(DisplayName = "For Using"),
	FastUsing    UMETA(DisplayName = "For Fast Using"),
	Resource     UMETA(DisplayName = "Resource"),
	Weapon	     UMETA(DisplayName = "Weapon"),
	Ammo		 UMETA(DisplayName = "Ammo"),
	Cloth		 UMETA(DisplayName = "Cloth"),
	Key		     UMETA(DisplayName = "Key")
};

UENUM(BlueprintType)
enum class EWK_SlotsType : uint8 {
	Inventory UMETA(DisplayName = "Inventory slots"),
	Fast      UMETA(DisplayName = "Fast slots"),
	Equip     UMETA(DisplayName = "Equip Slots"),
};

USTRUCT(BlueprintType)
struct FItemInfo {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString itemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* itemThumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWK_ItemType itemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* itemStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* itemSkeletal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AWK_Item> itemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor itemColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AWK_Item> Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Stackeble;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxStack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Useble;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Immediately (fast pick up)"))
	bool Immediately = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ClothSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int WeaponID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AmmoId;
};

USTRUCT(BlueprintType)
struct FItemSlot {
	
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ID = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Amount = 0;

};

USTRUCT(BlueprintType)
struct FItemFastSlot {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ID = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Amount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Active = false;

};

USTRUCT(BlueprintType)
struct FItemsData : public FTableRowBase
{
	GENERATED_BODY()
public:

	/** Item ID **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ID;

	/** Item struct **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemInfo itemInfo;

	/** description **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class WK_INVENTORY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();



	UFUNCTION(BlueprintCallable, Category = "Inventory Plugin")
	bool AddItem(AWK_PickUpActor* PickActor, int ID, int Amount);

	UFUNCTION(BlueprintPure, Category = "Inventory Plugin")
	FItemInfo GetItemInfo(int id);

	UFUNCTION(BlueprintCallable, Category = "Inventory Plugin")
	void SwapItems(int indexIn, int indexOut);

	UFUNCTION(BlueprintCallable, Category = "Inventory Plugin")
	bool UseItemAtIndex(EWK_SlotsType SlotsType, int SlotIndex, int Amount);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory Plugin")
	void SetNearItem(AWK_PickUpActor* PickActor, bool Activate);

	UFUNCTION(BlueprintCallable, Category = "Inventory Plugin")
	void UseItemByID(int id, int Amount);

	UFUNCTION(BlueprintCallable, Category = "Inventory Plugin")
	void FastUseItemFromPickUp(AWK_PickUpActor* PickActor, int ID, int Amount);

	//New Functions

	UFUNCTION(BlueprintCallable, Category = "Inventory Plugin")
	void AddItemToFastSlot(int indexIn, int indexOut);

	UFUNCTION(BlueprintCallable, Category = "Inventory Plugin")
	void AddItemToEquipSlot(int indexIn, int indexOut);

	UFUNCTION(BlueprintCallable, Category = "Inventory Plugin")
	void AddItemFromFastSlot(int indexIn, int indexOut);

	UFUNCTION(BlueprintCallable, Category = "Inventory Plugin")
	void AddItemFromEquipSlot(int indexIn, int indexOut);



protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:

	void GenerateSlots();
	void PreSaveGame();
	int SearhSlotForStack(int it_id, int it_maxStack);
	int SearchEmptySlot();



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Settings
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", meta = (DisplayName = "Inventory type"))
	EWK_OwnerType InventoryType = EWK_OwnerType::Character;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	int AmountInventorySlots = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	int AmountFastSlots = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	int AmountEquipSlots = 0;

	// Slots
	UPROPERTY(VisibleDefaultsOnly, SaveGame, BlueprintReadWrite, Category = "Slots")
	TArray<FItemSlot> InventorySlots;

	UPROPERTY(VisibleDefaultsOnly, SaveGame, BlueprintReadWrite, Category = "Slots")
	TArray<FItemFastSlot> FastSlots;

	UPROPERTY(VisibleDefaultsOnly, SaveGame, BlueprintReadWrite, Category = "Slots")
	TArray<FItemSlot> EquipSlots;

	// Start Slots
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Slots")
	TArray<FItemSlot> StartInventorySlots;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Slots")
	TArray<FItemFastSlot> StartFastSlots;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Slots")
	TArray<FItemSlot> StartEquipSlots;

	//Data
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	UDataTable* ItemBase;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	bool UseStacks;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", meta = (DisplayName = "Using indexes of Equip slots"))
	bool UseEquipSlotsIndexes;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", meta = (DisplayName = "Using indexes of Fast slots"))
	bool UseFastSlotsIndexes;

	// Pick ups
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Pick Ups")
	AWK_PickUpActor* NearPickActor;
	
public:

#pragma region BlueprintImplementableEvents

	UFUNCTION(BlueprintImplementableEvent)
	void CantUseEvent(FItemInfo ThisItem, int ItemAmount);

	UFUNCTION(BlueprintImplementableEvent)
	void UsedItemEvent(FItemInfo ThisItem, int ItemAmount);

#pragma endregion

};
