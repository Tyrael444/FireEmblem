// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FEInventoryComponent.generated.h"

class UFEBaseItem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFEOnItemEquipped, const UFEBaseItem*, anEquippedItem, bool, bIsEquipped);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIREEMBLEM_API UFEInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UFEInventoryComponent();


	/********
	* Inventory methods
	********/

	/* Setup the inventory by creating the various instances required
	* If bAutoEquip is set to true, will automatically equip the first possible item
	*/
	void SetupInventory(bool bAutoEquip = true);

	/* Add an item to the inventory 
	* If bEquipItem is set to true, will equip the newly added item
	*/
	void AddItem(const TObjectPtr<UFEBaseItem> anItem, bool bEquipItem = false);

	/* Create an instance from anItem and add it to the inventory 
	* If bEquipItem is set to true, will equip the newly added item
	*/
	void CreateAndAddItem(const TSubclassOf<UFEBaseItem>& anItem, bool bEquipItem = false);

	/* Remove an item from the inventory.
	* Can auto equip the first possible item if bAutoEquip is set to true
	*/
	void RemoveItem(const int anItemIndex, bool bAutoEquip = false);

	/* Replace the item at index anItemIndexToReplace with anItemToAdd
	*  Will automatically equip the newly added item if bEquipItem is set to true 
	*  If the removed item is the currently equipped one, and you want to swap it, set bReplaceIfEquipped to true
	*/
	void ReplaceItem(const TObjectPtr<UFEBaseItem> anItemToAdd, const int anItemIndexToReplace, bool bReplaceIfEquipped = true, bool bEquipItem = false);

	/* Replace the item at anItemIndexToReplace with an instance base on anItemToAdd
	* Will automatically equip the newly added item if bEquipItem is set to true
	* If the removed item is the currently equipped one, and you want to swap it, set bReplaceIfEquipped to true
	*/
	void CreateAndReplace(const TSubclassOf<UFEBaseItem>& anItemToAdd, const int anItemIndexToReplace, bool bReplaceIfEquipped = true, bool bEquipItem = false);

	/* Check if this item can equipped by the owner character */
	bool CanEquipItem(const TObjectPtr<UFEBaseItem> anItem) const;

	/* Will set this item as the currently equipped one
	* Will also process the item buffs/etc
	* Should be called by default when adding a first equippable item in the inventory (in case you empty it beforehand)
	*/
	void EquipItem(const TObjectPtr<UFEBaseItem> anItem);

	/* Will unequip the currently equipped item
	* Will also set the current equipped item to nullptr
	*/
	void UnequipItem();

	/* Access to the currently equipped item. Can return nullptr */
	const UFEBaseItem* GetEquippedItem() const;


public:


	/********
	* Delegate
	********/

	/* Event called when equipping (or removing) an item
	* bIsEquipped is set to true when equipping, otherwise to false
	*/
	UPROPERTY(BlueprintAssignable)
	FFEOnItemEquipped OnItemEquipped;


protected:


	/********
	* Items
	********/

	/* Defines the items this inventory currently have
	* The fixed size is completely "random", might change in future 
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory", meta = (EditFixedSize = "8"))
	TArray<TSubclassOf<UFEBaseItem>> Items;

	/* Items instances */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<TObjectPtr<UFEBaseItem>> ItemsInstances;

	/* Currently equipped item */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TObjectPtr<UFEBaseItem> EquippedItem;
};