#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <memory>
#include "Item.h"

namespace GameCore {

// Player class demonstrating encapsulation, member functions, and smart pointers
class Player {
private:
    std::string name;
    int hp;
    int maxHP;
    int attack;
    int defense;
    int level;
    int xp;
    int xpToNextLevel;
    
    // Inventory using shared_ptr for shared ownership
    std::vector<std::shared_ptr<Item>> inventory;
    
    // Private helper function for leveling up
    void levelUp();

public:
    // Constructor demonstrating member initializer list
    Player(const std::string& name, int hp, int attack, int defense);
    
    // Copy constructor (demonstrating rule of five)
    Player(const Player& other);
    
    // Copy assignment operator
    Player& operator=(const Player& other);
    
    // Move constructor
    Player(Player&& other) noexcept;
    
    // Move assignment operator
    Player& operator=(Player&& other) noexcept;
    
    // Destructor
    ~Player();
    
    // Getters (const member functions)
    const std::string& getName() const { return name; }
    int getHP() const { return hp; }
    int getMaxHP() const { return maxHP; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }
    int getLevel() const { return level; }
    int getXP() const { return xp; }
    int getXPToNextLevel() const { return xpToNextLevel; }
    size_t getInventorySize() const { return inventory.size(); }
    
    // Setters
    void setHP(int newHP) { hp = std::min(newHP, maxHP); }
    void setAttack(int newAttack) { attack = newAttack; }
    void setDefense(int newDefense) { defense = newDefense; }
    
    // Action methods
    void takeDamage(int damage);
    void heal(int amount);
    void gainXP(int amount);
    
    // Inventory management using shared_ptr
    void addItem(std::shared_ptr<Item> item);
    void useItem(size_t index);
    void displayInventory() const;
    
    // Operator overloading
    bool operator==(const Player& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Player& player);
};

} // namespace GameCore

#endif // PLAYER_H
