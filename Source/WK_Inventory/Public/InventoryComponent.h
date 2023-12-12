// Woodykoff production. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WK_Item.h"

#include "InventoryComponent.generated.h"

UENUM(BlueprintType)
enum class EWK_ItemType : uint8 {
	Quest        UMETA(DisplayName = "For Quest"),
	Resource     UMETA(DisplayName = "Resource"),
	Weapon	     UMETA(DisplayName = "Weapon"),
	Ammo		 UMETA(DisplayName = "Ammo"),
	Key		     UMETA(DisplayName = "Key")
};

USTRUCT()
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
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WK_INVENTORY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
