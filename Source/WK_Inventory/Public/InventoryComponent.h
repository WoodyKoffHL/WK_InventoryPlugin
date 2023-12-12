// Woodykoff production. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WK_Inventory.h"
#include "WK_Item.h"

#include "InventoryComponent.generated.h"

UENUM(BlueprintType)
enum class EWK_ItemType : uint8 {
	Quest        UMETA(DisplayName = "For Quest"),
	Resource     UMETA(DisplayName = "Resource"),
	Weapon	     UMETA(DisplayName = "Weapon"),
	Ammo		 UMETA(DisplayName = "Ammo"),
	Cloth		 UMETA(DisplayName = "Ammo"),
	Key		     UMETA(DisplayName = "Key")
};

USTRUCT(BlueprintType)
struct FItemInfo {

	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FString itemName;

	UPROPERTY(EditAnywhere)
	UTexture2D* itemThumbnail;

	UPROPERTY(EditAnywhere)
	EWK_ItemType itemType;

	UPROPERTY(EditAnywhere)
	UStaticMesh* itemStaticMesh;

	UPROPERTY(EditAnywhere)
	USkeletalMesh* itemSkeletal;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AWK_Item> itemClass;

	UPROPERTY(EditAnywhere)
	FColor itemColor;

	UPROPERTY(EditAnywhere)
	bool Stackeble;

	UPROPERTY(EditAnywhere)
	int MaxStack;

	UPROPERTY(EditAnywhere)
	bool Useble;

	UPROPERTY(EditAnywhere)
	int ClothSlot;

	UPROPERTY(EditAnywhere)
	int WeaponSlot;

	UPROPERTY(EditAnywhere)
	int AmmoId;
};

USTRUCT(BlueprintType)
struct FItemSlot {
	
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	int ID;

	UPROPERTY(EditAnywhere)
	int Amount;

};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class WK_INVENTORY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	void GenerateSlots();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Settings
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
	TArray<FItemSlot> FastSlots;
	UPROPERTY(VisibleDefaultsOnly, SaveGame, BlueprintReadWrite, Category = "Slots")
	TArray<FItemSlot> EquipSlots;

	// Start Slots
	UPROPERTY(EditDefaultsOnly, SaveGame, BlueprintReadWrite, Category = "Slots")
	TArray<FItemSlot> StartInventorySlots;
	UPROPERTY(EditDefaultsOnly, SaveGame, BlueprintReadWrite, Category = "Slots")
	TArray<FItemSlot> StartFastSlots;
	UPROPERTY(EditDefaultsOnly, SaveGame, BlueprintReadWrite, Category = "Slots")
	TArray<FItemSlot> StartEquipSlots;
		
};
