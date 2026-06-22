#include "Player.h"
#include <iostream>
#include <algorithm>
#include "GameUtils.h"

namespace GameCore {

// Constructor with member initializer list
Player::Player(const std::string& name, int hp, int attack, int defense)
    : name(name), hp(hp), maxHP(hp), attack(attack), defense(defense),
      level(1), xp(0), xpToNextLevel(100) {
}

// Copy constructor
Player::Player(const Player& other)
    : name(other.name), hp(other.hp), maxHP(other.maxHP),
      attack(other.attack), defense(other.defense), level(other.level),
      xp(other.xp), xpToNextLevel(other.xpToNextLevel),
      inventory(other.inventory) {
}

// Copy assignment operator
Player& Player::operator=(const Player& other) {
    if (this != &other) {
        name = other.name;
        hp = other.hp;
        maxHP = other.maxHP;
        attack = other.attack;
        defense = other.defense;
        level = other.level;
        xp = other.xp;
        xpToNextLevel = other.xpToNextLevel;
        inventory = other.inventory;
    }
    return *this;
}

// Move constructor
Player::Player(Player&& other) noexcept
    : name(std::move(other.name)), hp(other.hp), maxHP(other.maxHP),
      attack(other.attack), defense(other.defense), level(other.level),
      xp(other.xp), xpToNextLevel(other.xpToNextLevel),
      inventory(std::move(other.inventory)) {
    other.hp = 0;
    other.maxHP = 0;
    other.attack = 0;
    other.defense = 0;
    other.level = 0;
    other.xp = 0;
    other.xpToNextLevel = 0;
}

// Move assignment operator
Player& Player::operator=(Player&& other) noexcept {
    if (this != &other) {
        name = std::move(other.name);
        hp = other.hp;
        maxHP = other.maxHP;
        attack = other.attack;
        defense = other.defense;
        level = other.level;
        xp = other.xp;
        xpToNextLevel = other.xpToNextLevel;
        inventory = std::move(other.inventory);
        
        other.hp = 0;
        other.maxHP = 0;
        other.attack = 0;
        other.defense = 0;
        other.level = 0;
        other.xp = 0;
        other.xpToNextLevel = 0;
    }
    return *this;
}

// Destructor
Player::~Player() {
    // Smart pointers automatically clean up inventory
}

void Player::levelUp() {
    level++;
    xp -= xpToNextLevel;
    xpToNextLevel = static_cast<int>(xpToNextLevel * 1.5);
    
    // Increase stats
    maxHP += 10;
    hp = maxHP;
    attack += 3;
    defense += 2;
    
    GameUtils::Console::setColor(GameUtils::ConsoleColor::YELLOW);
    std::cout << "\n*** LEVEL UP! You are now level " << level << " ***" << std::endl;
    GameUtils::Console::resetColor();
}

void Player::takeDamage(int damage) {
    // Reduce damage by defense
    int actualDamage = std::max(1, damage - defense);
    hp -= actualDamage;
    
    GameUtils::Console::setColor(GameUtils::ConsoleColor::RED);
    std::cout << name << " took " << actualDamage << " damage!" << std::endl;
    GameUtils::Console::resetColor();
    
    if (hp <= 0) {
        hp = 0;
    }
}

void Player::heal(int amount) {
    hp = std::min(hp + amount, maxHP);
    
    GameUtils::Console::setColor(GameUtils::ConsoleColor::GREEN);
    std::cout << name << " healed for " << amount << " HP!" << std::endl;
    GameUtils::Console::resetColor();
}

void Player::gainXP(int amount) {
    xp += amount;
    
    while (xp >= xpToNextLevel) {
        levelUp();
    }
}

void Player::addItem(std::shared_ptr<Item> item) {
    inventory.push_back(item);
}

void Player::useItem(size_t index) {
    if (index >= inventory.size()) {
        std::cout << "Invalid item index!" << std::endl;
        return;
    }
    
    auto item = inventory[index];
    item->use(*this);
    
    // Remove consumable items after use
    if (item->isConsumable()) {
        inventory.erase(inventory.begin() + index);
    }
}

void Player::displayInventory() const {
    GameUtils::Console::setColor(GameUtils::ConsoleColor::CYAN);
    std::cout << "\n=== INVENTORY ===" << std::endl;
    
    if (inventory.empty()) {
        std::cout << "Your inventory is empty." << std::endl;
    } else {
        for (size_t i = 0; i < inventory.size(); ++i) {
            std::cout << (i + 1) << ". " << inventory[i]->getName();
            if (inventory[i]->isConsumable()) {
                std::cout << " (Consumable)";
            }
            std::cout << std::endl;
            std::cout << "   " << inventory[i]->getDescription() << std::endl;
        }
    }
    GameUtils::Console::resetColor();
}

bool Player::operator==(const Player& other) const {
    return name == other.name && level == other.level;
}

std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << player.name << " (Lvl " << player.level << ") - HP: " 
       << player.hp << "/" << player.maxHP;
    return os;
}

} // namespace GameCore
