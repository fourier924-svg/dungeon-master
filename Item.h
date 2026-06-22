#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <memory>
#include <random>
#include <iostream>

namespace GameCore {

// Enum for item types
enum class ItemType {
    WEAPON,
    POTION,
    ARMOR,
    MISC
};

// Enum for weapon types
enum class WeaponType {
    SWORD,
    AXE,
    BOW,
    STAFF
};

// Forward declaration
class Player;

// Abstract base class for items - demonstrates polymorphism
class Item {
protected:
    std::string name;
    std::string description;
    ItemType type;
    bool consumable;
    
public:
    Item(const std::string& name, const std::string& description, ItemType type, bool consumable)
        : name(name), description(description), type(type), consumable(consumable) {}
    
    virtual ~Item() = default;
    
    // Pure virtual function - must be implemented by derived classes
    virtual void use(Player& player) = 0;
    
    // Virtual function with default implementation
    virtual void display() const {
        std::cout << name << ": " << description << std::endl;
    }
    
    // Getters
    const std::string& getName() const { return name; }
    const std::string& getDescription() const { return description; }
    ItemType getType() const { return type; }
    bool isConsumable() const { return consumable; }
};

// Template class for stackable items
template<typename T>
class StackableItem : public Item {
private:
    int stackSize;
    int maxStackSize;
    
public:
    StackableItem(const std::string& name, const std::string& description, ItemType type, 
                  int maxStack = 99)
        : Item(name, description, type, true), stackSize(1), maxStackSize(maxStack) {}
    
    int getStackSize() const { return stackSize; }
    int getMaxStackSize() const { return maxStackSize; }
    
    bool addToStack(int amount) {
        if (stackSize + amount <= maxStackSize) {
            stackSize += amount;
            return true;
        }
        return false;
    }
    
    bool removeFromStack(int amount) {
        if (stackSize >= amount) {
            stackSize -= amount;
            return true;
        }
        return false;
    }
    
    void display() const override {
        std::cout << name << " x" << stackSize << ": " << description << std::endl;
    }
};

// Health Potion class
class HealthPotion : public StackableItem<HealthPotion> {
private:
    int healAmount;
    
public:
    HealthPotion(const std::string& name, int healAmount)
        : StackableItem<HealthPotion>(name, "Restores " + std::to_string(healAmount) + " HP", 
                                       ItemType::POTION, 99), healAmount(healAmount) {}
    
    void use(Player& player) override;
};

// Weapon class
class Weapon : public Item {
private:
    int attackBonus;
    WeaponType weaponType;
    
public:
    Weapon(const std::string& name, int attackBonus, WeaponType weaponType)
        : Item(name, "Weapon with " + std::to_string(attackBonus) + " attack bonus", 
               ItemType::WEAPON, false), attackBonus(attackBonus), weaponType(weaponType) {}
    
    void use(Player& player) override;
    
    int getAttackBonus() const { return attackBonus; }
    WeaponType getWeaponType() const { return weaponType; }
};

// Armor class
class Armor : public Item {
private:
    int defenseBonus;
    
public:
    Armor(const std::string& name, int defenseBonus)
        : Item(name, "Armor with " + std::to_string(defenseBonus) + " defense bonus", 
               ItemType::ARMOR, false), defenseBonus(defenseBonus) {}
    
    void use(Player& player) override;
    
    int getDefenseBonus() const { return defenseBonus; }
};

// Item Factory class - demonstrates Factory pattern
class ItemFactory {
public:
    // Static method to create random items
    static std::shared_ptr<Item> createRandomItem(int playerLevel);
    
    // Specific creation methods
    static std::shared_ptr<Item> createHealthPotion(int level);
    static std::shared_ptr<Item> createWeapon(int level);
    static std::shared_ptr<Item> createArmor(int level);
};

} // namespace GameCore

#endif // ITEM_H
