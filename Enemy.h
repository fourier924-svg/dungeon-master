#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <memory>

namespace GameCore {

// Enum for enemy types
enum class EnemyType {
    GOBLIN,
    ORC,
    DRAGON
};

// Abstract base class demonstrating polymorphism and pure virtual functions
class Enemy {
protected:
    std::string name;
    int hp;
    int maxHP;
    int attack;
    int defense;
    int level;
    int xpValue;
    
public:
    // Constructor
    Enemy(const std::string& name, int hp, int attack, int defense, int level, int xpValue);
    
    // Virtual destructor for proper polymorphic cleanup
    virtual ~Enemy() = default;
    
    // Pure virtual function - must be implemented by derived classes
    virtual void specialAbility() = 0;
    
    // Virtual function that can be overridden
    virtual void display() const;
    
    // Getters
    const std::string& getName() const { return name; }
    int getHP() const { return hp; }
    int getMaxHP() const { return maxHP; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }
    int getLevel() const { return level; }
    int getXPValue() const { return xpValue; }
    
    // Setters
    void setHP(int newHP) { hp = std::min(newHP, maxHP); }
    
    // Action methods
    void takeDamage(int damage);
    bool isAlive() const { return hp > 0; }
    
    // Factory method pattern
    static std::unique_ptr<Enemy> createEnemy(EnemyType type, int level);
};

// Derived class: Goblin
class Goblin : public Enemy {
public:
    explicit Goblin(int level);
    
    // Override pure virtual function
    void specialAbility() override;
    
    // Override virtual function
    void display() const override;
};

// Derived class: Orc
class Orc : public Enemy {
public:
    explicit Orc(int level);
    
    // Override pure virtual function
    void specialAbility() override;
    
    // Override virtual function
    void display() const override;
};

// Derived class: Dragon
class Dragon : public Enemy {
public:
    explicit Dragon(int level);
    
    // Override pure virtual function
    void specialAbility() override;
    
    // Override virtual function
    void display() const override;
};

} // namespace GameCore

#endif // ENEMY_H
