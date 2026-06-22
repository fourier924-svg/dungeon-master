#include "Enemy.h"
#include <iostream>
#include <algorithm>
#include "GameUtils.h"

namespace GameCore {

// Base Enemy class constructor
Enemy::Enemy(const std::string& name, int hp, int attack, int defense, int level, int xpValue)
    : name(name), hp(hp), maxHP(hp), attack(attack), defense(defense),
      level(level), xpValue(xpValue) {
}

void Enemy::display() const {
    GameUtils::Console::setColor(GameUtils::ConsoleColor::RED);
    std::cout << name << " (Lvl " << level << ") - HP: " << hp << "/" << maxHP << std::endl;
    GameUtils::Console::resetColor();
}

void Enemy::takeDamage(int damage) {
    int actualDamage = std::max(1, damage - defense);
    hp -= actualDamage;
    
    GameUtils::Console::setColor(GameUtils::ConsoleColor::RED);
    std::cout << name << " took " << actualDamage << " damage!" << std::endl;
    GameUtils::Console::resetColor();
    
    if (hp < 0) hp = 0;
}

// Factory method implementation
std::unique_ptr<Enemy> Enemy::createEnemy(EnemyType type, int level) {
    switch(type) {
        case EnemyType::GOBLIN:
            return std::make_unique<Goblin>(level);
        case EnemyType::ORC:
            return std::make_unique<Orc>(level);
        case EnemyType::DRAGON:
            return std::make_unique<Dragon>(level);
        default:
            return std::make_unique<Goblin>(level);
    }
}

// Goblin implementation
Goblin::Goblin(int level)
    : Enemy("Goblin", 50 + (level * 10), 12 + (level * 3), 3 + level, level, 25 + (level * 10)) {
}

void Goblin::specialAbility() {
    GameUtils::Console::setColor(GameUtils::ConsoleColor::GREEN);
    std::cout << "The Goblin uses its agility to dodge!" << std::endl;
    GameUtils::Console::resetColor();
    defense += 2;
}

void Goblin::display() const {
    GameUtils::Console::setColor(GameUtils::ConsoleColor::GREEN);
    std::cout << "      /\\      " << std::endl;
    std::cout << "     /  \\     " << std::endl;
    std::cout << "    /    \\    " << std::endl;
    std::cout << "   /  o o  \\   " << std::endl;
    std::cout << "   \\   ^   /   " << std::endl;
    std::cout << "    \\ \\_/ /    " << std::endl;
    std::cout << "     \\___/     " << std::endl;
    GameUtils::Console::resetColor();
    Enemy::display();
}

// Orc implementation
Orc::Orc(int level)
    : Enemy("Orc", 100 + (level * 15), 20 + (level * 4), 8 + (level * 2), level, 50 + (level * 15)) {
}

void Orc::specialAbility() {
    GameUtils::Console::setColor(GameUtils::ConsoleColor::RED);
    std::cout << "The Orc goes into a rage! Attack increased!" << std::endl;
    GameUtils::Console::resetColor();
    attack += 5;
}

void Orc::display() const {
    GameUtils::Console::setColor(GameUtils::ConsoleColor::RED);
    std::cout << "      /\\      " << std::endl;
    std::cout << "     /  \\     " << std::endl;
    std::cout << "    /    \\    " << std::endl;
    std::cout << "   |  O O  |   " << std::endl;
    std::cout << "   |   ^   |   " << std::endl;
    std::cout << "   |  \\_/  |   " << std::endl;
    std::cout << "   |       |   " << std::endl;
    std::cout << "  /|       |\\  " << std::endl;
    std::cout << " / |       | \\ " << std::endl;
    std::cout << "   |_______|   " << std::endl;
    GameUtils::Console::resetColor();
    Enemy::display();
}

// Dragon implementation
Dragon::Dragon(int level)
    : Enemy("Dragon", 200 + (level * 25), 35 + (level * 6), 15 + (level * 3), level, 100 + (level * 25)) {
}

void Dragon::specialAbility() {
    GameUtils::Console::setColor(GameUtils::ConsoleColor::YELLOW);
    std::cout << "The Dragon breathes fire! Massive damage!" << std::endl;
    GameUtils::Console::resetColor();
    attack += 10;
}

void Dragon::display() const {
    GameUtils::Console::setColor(GameUtils::ConsoleColor::YELLOW);
    std::cout << "         /\\         " << std::endl;
    std::cout << "        /  \\        " << std::endl;
    std::cout << "       /    \\       " << std::endl;
    std::cout << "      /  o o  \\      " << std::endl;
    std::cout << "      \\   ^   /      " << std::endl;
    std::cout << "       \\ \\_/ /       " << std::endl;
    std::cout << "        \\___/        " << std::endl;
    std::cout << "       /|   |\\       " << std::endl;
    std::cout << "      / |   | \\      " << std::endl;
    std::cout << "     /  |   |  \\     " << std::endl;
    std::cout << "    /   |   |   \\    " << std::endl;
    std::cout << "   /    |   |    \\   " << std::endl;
    std::cout << "  /     |   |     \\  " << std::endl;
    std::cout << " /______|___|______\\ " << std::endl;
    GameUtils::Console::resetColor();
    Enemy::display();
}

} // namespace GameCore
