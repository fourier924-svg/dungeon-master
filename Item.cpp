#include "Item.h"
#include "Player.h"
#include <iostream>
#include <random>
#include "GameUtils.h"

namespace GameCore {

// HealthPotion implementation
void HealthPotion::use(Player& player) {
    player.heal(healAmount);
    std::cout << "Used " << name << "!" << std::endl;
}

// Weapon implementation
void Weapon::use(Player& player) {
    player.setAttack(player.getAttack() + attackBonus);
    player.setEquippedWeapon(this);
    std::cout << "Equipped " << name << "! Attack increased by " << attackBonus << "!" << std::endl;
}

// Armor implementation
void Armor::use(Player& player) {
    player.setDefense(player.getDefense() + defenseBonus);
    std::cout << "Equipped " << name << "! Defense increased by " << defenseBonus << "!" << std::endl;
}

// ItemFactory implementation
std::shared_ptr<Item> ItemFactory::createRandomItem(int playerLevel) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 3);
    
    int choice = dist(gen);
    
    switch(choice) {
        case 1:
            return createHealthPotion(playerLevel);
        case 2:
            return createWeapon(playerLevel);
        case 3:
            return createArmor(playerLevel);
        default:
            return createHealthPotion(playerLevel);
    }
}

std::shared_ptr<Item> ItemFactory::createHealthPotion(int level) {
    int healAmount = 20 + (level * 5);
    return std::make_shared<HealthPotion>("Health Potion", healAmount);
}

std::shared_ptr<Item> ItemFactory::createWeapon(int level) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> weaponDist(0, 3);
    
    WeaponType type = static_cast<WeaponType>(weaponDist(gen));
    int attackBonus = 5 + (level * 3);
    
    std::string name;
    switch(type) {
        case WeaponType::SWORD:
            name = "Steel Sword";
            break;
        case WeaponType::AXE:
            name = "Battle Axe";
            break;
        case WeaponType::BOW:
            name = "Long Bow";
            break;
        case WeaponType::STAFF:
            name = "Magic Staff";
            break;
    }
    
    return std::make_shared<Weapon>(name, attackBonus, type);
}

std::shared_ptr<Item> ItemFactory::createArmor(int level) {
    int defenseBonus = 3 + (level * 2);
    std::string name = "Iron Armor";
    
    return std::make_shared<Armor>(name, defenseBonus);
}

} // namespace GameCore
