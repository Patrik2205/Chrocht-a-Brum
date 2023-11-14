#define BOOST_TEST_MODULE UnitTests
#include <boost/test/included/unit_test.hpp>
#include "Main.cpp"

BOOST_AUTO_TEST_SUITE(ItemTests)

BOOST_AUTO_TEST_CASE(ItemGetNameAndWeight)
{
    Item item("TestItem", 10);
    BOOST_CHECK(item.getName() == "TestItem");
    BOOST_CHECK(item.getWeight() == 10);
}

BOOST_AUTO_TEST_CASE(StackableItemQuantity)
{
    StackableItem stackableItem("TestStackableItem", 5, 3);
    BOOST_CHECK(stackableItem.getQuantity() == 3);

    stackableItem.increaseQuantity(2);
    BOOST_CHECK(stackableItem.getQuantity() == 5);

    BOOST_CHECK(stackableItem.Type() == "StackableItem");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(WeaponTests)

BOOST_AUTO_TEST_CASE(LightWeaponDamage)
{
    LightWeapon lightWeapon("TestLightWeapon", 8);
    BOOST_CHECK(lightWeapon.getDamage() >= 1 && lightWeapon.getDamage() <= 6);
}

BOOST_AUTO_TEST_CASE(HeavyWeaponDamage)
{
    HeavyWeapon heavyWeapon("TestHeavyWeapon", 12);
    BOOST_CHECK(heavyWeapon.getDamage() >= 5 && heavyWeapon.getDamage() <= 10);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ShieldTests)

BOOST_AUTO_TEST_CASE(ShieldProtection)
{
    Shield shield("TestShield", 6);
    BOOST_CHECK(shield.getProtection() >= 1 && shield.getProtection() <= 5);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ArmorTests)

BOOST_AUTO_TEST_CASE(ArmorProtection)
{
    Armor armor("TestArmor", 7);
    BOOST_CHECK(armor.getProtection() >= 1 && armor.getProtection() <= 4);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CoinsTests)

BOOST_AUTO_TEST_CASE(CopperCoinTest)
{
    CopperCoin copperCoin(1);
    BOOST_CHECK_EQUAL(copperCoin.Type(), "CopperCoin");
}

BOOST_AUTO_TEST_CASE(SilverCoinTest)
{
    SilverCoin silverCoin(1);
    BOOST_CHECK_EQUAL(silverCoin.Type(), "SilverCoin");
}

BOOST_AUTO_TEST_CASE(GoldCoinTest)
{
    GoldCoin goldCoin(1);
    BOOST_CHECK_EQUAL(goldCoin.Type(), "GoldCoin");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(VitalityPotionsTest)

BOOST_AUTO_TEST_CASE(VitalityPotionTest)
{
    VitalityPotion vitalityPotion("Potion", 140);
    BOOST_CHECK(vitalityPotion.getHealthMultiplier() > 0);
    BOOST_CHECK_EQUAL(vitalityPotion.Type(), "Vitality Potion");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(InventoryTests)

BOOST_AUTO_TEST_CASE(InventoryAddToInventory)
{
    Inventory inventory;
    LightWeapon lightWeapon("TestLightWeapon", 8);

    // Add an item to the inventory
    inventory.addToInventory(&lightWeapon, 1);

    // Check if the item is added successfully
    BOOST_CHECK(!inventory.InventoryLightWeapon.empty());
    BOOST_CHECK(inventory.InventoryLightWeapon[1].getName() == "TestLightWeapon");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CharacterTests)

BOOST_AUTO_TEST_CASE(CharacterCreation)
{
    Character character("TestCharacter");
    BOOST_CHECK(character.getName() == "TestCharacter");
    BOOST_CHECK(character.getCurrentHP() > 0);
    BOOST_CHECK(character.getAttackDamage() >= 0);
    BOOST_CHECK(character.getAgility() >= 0);
    BOOST_CHECK(character.getProtection() >= 0);
}

BOOST_AUTO_TEST_CASE(CharacterInventoryManagement)
{
    Character character("TestCharacter");
    LightWeapon lightWeapon("TestLightWeapon", 8);

    // Add an item to the character's inventory
    character.addToInventory(&lightWeapon, 1);

    // Check if the item is added successfully to both inventory and character
    BOOST_CHECK(!character.InventoryLightWeapon.empty());
    BOOST_CHECK(character.InventoryLightWeapon[1].getName() == "TestLightWeapon");
    BOOST_CHECK(character.getCurrentCarryWeight() > 0);
}

BOOST_AUTO_TEST_SUITE_END()
