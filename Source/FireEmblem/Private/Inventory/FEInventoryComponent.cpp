// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/FEInventoryComponent.h"
#include "DataAsset/Item/FEBaseItem.h"
#include "Character/FEBaseCharacter.h"

// Sets default values for this component's properties
UFEInventoryComponent::UFEInventoryComponent()
{
}

void UFEInventoryComponent::SetupInventory(bool bAutoEquip /*= true*/)
{
	for (auto item : Items)
	{
		UFEBaseItem* itemToAdd = NewObject<UFEBaseItem>(this, item.Get());
		ItemsInstances.Add(itemToAdd);

		if (bAutoEquip && CanEquipItem(itemToAdd))
		{
			bAutoEquip = false;
			EquipItem(itemToAdd);
		}
	}
}

void UFEInventoryComponent::AddItem(const TObjectPtr<UFEBaseItem> anItem, bool bEquipItem /*= false*/)
{
	check(anItem);

	for (int i = 0; i < ItemsInstances.Num(); ++i)
	{
		if (!ItemsInstances[i])
		{
			ItemsInstances[i] = anItem;
		}
	}

	if (bEquipItem)
		EquipItem(anItem);
}

void UFEInventoryComponent::CreateAndAddItem(const TSubclassOf<UFEBaseClass>& anItem, bool bEquipItem /*= false*/)
{
	TObjectPtr<UFEBaseItem> item = NewObject<UFEBaseItem>(this, anItem.Get());
	check(item);

	for (int i = 0; i < ItemsInstances.Num(); ++i)
	{
		if (!ItemsInstances[i])
		{
			ItemsInstances[i] = item;
		}
	}

	if (bEquipItem)
		EquipItem(item);
}

void UFEInventoryComponent::RemoveItem(const int anItemIndex, bool bAutoEquip /*= false*/)
{
	check(anItemIndex >= 0);
	check(ItemsInstances.Num() < anItemIndex);

	UFEBaseItem* item = ItemsInstances[anItemIndex];
	if (item == EquippedItem)
		UnequipItem();

	ItemsInstances.RemoveSingle(item);

	if (bAutoEquip)
	{
		for (int i = 0; i < ItemsInstances.Num(); ++i)
		{
			if (CanEquipItem(ItemsInstances[i]))
			{
				EquipItem(ItemsInstances[i]);
			}
		}
	}
}

void UFEInventoryComponent::ReplaceItem(const TObjectPtr<UFEBaseItem> anItemToAdd, const int anItemIndexToReplace, bool bReplaceIfEquipped /*= true*/, bool bEquipItem /*= false*/)
{
	bool needReequip = false;
	if (EquippedItem == ItemsInstances[anItemIndexToReplace] && bReplaceIfEquipped)
	{
		needReequip = true;
	}

	RemoveItem(anItemIndexToReplace);
	ItemsInstances[anItemIndexToReplace] = anItemToAdd;

	if (needReequip || bEquipItem)
		EquipItem(anItemToAdd);
}

void UFEInventoryComponent::CreateAndReplace(const TSubclassOf<UFEBaseItem>& anItemToAdd, const int anItemIndexToReplace, bool bReplaceIfEquipped /*= true*/, bool bEquipItem /*= false*/)
{
	bool needReequip = false;
	if (EquippedItem == ItemsInstances[anItemIndexToReplace] && bReplaceIfEquipped)
	{
		needReequip = true;
	}

	RemoveItem(anItemIndexToReplace);
	TObjectPtr<UFEBaseItem> item = NewObject<UFEBaseItem>(this, anItemToAdd.Get());
	check(item);
	ItemsInstances[anItemIndexToReplace] = item;

	if (needReequip || bEquipItem)
		EquipItem(item);
}

bool UFEInventoryComponent::CanEquipItem(const TObjectPtr<UFEBaseItem> anItem) const
{
	/* will check if we can equip this item or not depending on object type, weapon mastery, etc */

	return true;
}

void UFEInventoryComponent::EquipItem(const TObjectPtr<UFEBaseItem> anItem)
{
	check(anItem);

	/* first, remove the currently equipped item to make sure to remove all the possible buffs, etc */
	if (EquippedItem)
		UnequipItem();

	EquippedItem = anItem;

	OnItemEquipped.Broadcast(EquippedItem, true);
}

void UFEInventoryComponent::UnequipItem()
{
	EquippedItem = nullptr;

	OnItemEquipped.Broadcast(EquippedItem, false);
}

const UFEBaseItem* UFEInventoryComponent::GetEquippedItem() const
{
	return EquippedItem;
}