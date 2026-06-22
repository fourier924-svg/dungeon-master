#include "CombatSystem.h"
#include "GameUtils.h"
#include <iostream>
#include <random>
#include <thread>
#include <chrono>

namespace GameCore {

void CombatSystem::battle(Player& player, Enemy& enemy) {
    GameUtils::Console::setColor(GameUtils::ConsoleColor::YELLOW);
    std::cout << "\n=== COMBAT STARTED ===" << std::endl;
    GameUtils::Console::resetColor();
    
    enemy.display();
    
    while (!isCombatOver(player, enemy)) {
        displayCombatStatus(player, enemy);
        
        // Player turn
        std::cout << "\nYour turn!" << std::endl;
        std::cout << "1. Attack" << std::endl;
        std::cout << "2. Use Item" << std::endl;
        std::cout << "3. Run" << std::endl;
        
        int choice;
        std::cout << "\nChoice: ";
        std::cin >> choice;
        
        switch(choice) {
            case 1:
                playerAttack(player, enemy);
                break;
            case 2:
                player.displayInventory();
                std::cout << "\nEnter item number to use (0 to cancel): ";
                int itemNum;
                std::cin >> itemNum;
                if (itemNum > 0) {
                    player.useItem(itemNum - 1);
                }
                break;
            case 3:
                if (GameUtils::Utils::randomInt(1, 100) <= 30) {
                    GameUtils::Console::setColor(GameUtils::ConsoleColor::GREEN);
                    std::cout << "You successfully ran away!" << std::endl;
                    GameUtils::Console::resetColor();
                    return;
                } else {
                    GameUtils::Console::setColor(GameUtils::ConsoleColor::RED);
                    std::cout << "You failed to run away!" << std::endl;
                    GameUtils::Console::resetColor();
                }
                break;
            default:
                std::cout << "Invalid choice!" << std::endl;
                continue;
        }
        
        // Check if enemy is defeated
        if (!enemy.isAlive()) {
            GameUtils::Console::setColor(GameUtils::ConsoleColor::GREEN);
            std::cout << "\nYou defeated the " << enemy.getName() << "!" << std::endl;
            GameUtils::Console::resetColor();
            return;
        }
        
        // Enemy turn
        GameUtils::Console::setColor(GameUtils::ConsoleColor::RED);
        std::cout << "\nEnemy's turn!" << std::endl;
        GameUtils::Console::resetColor();
        
        // Enemy might use special ability
        if (GameUtils::Utils::randomInt(1, 100) <= 25) {
            enemy.specialAbility();
        }
        
        enemyAttack(enemy, player);
        
        // Small delay for dramatic effect
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    
    GameUtils::Console::setColor(GameUtils::ConsoleColor::YELLOW);
    std::cout << "\n=== COMBAT ENDED ===" << std::endl;
    GameUtils::Console::resetColor();
}

void CombatSystem::playerAttack(Player& player, Enemy& enemy) {
    // Calculate damage with some randomness
    int baseDamage = player.getAttack();
    int variance = GameUtils::Utils::randomInt(-2, 2);
    int totalDamage = baseDamage + variance;
    
    GameUtils::Console::setColor(GameUtils::ConsoleColor::CYAN);
    std::cout << player.getName() << " attacks " << enemy.getName() << "!" << std::endl;
    GameUtils::Console::resetColor();
    
    enemy.takeDamage(totalDamage);
}

void CombatSystem::enemyAttack(const Enemy& enemy, Player& player) {
    // Calculate damage with some randomness
    int baseDamage = enemy.getAttack();
    int variance = GameUtils::Utils::randomInt(-2, 2);
    int totalDamage = baseDamage + variance;
    
    GameUtils::Console::setColor(GameUtils::ConsoleColor::RED);
    std::cout << enemy.getName() << " attacks " << player.getName() << "!" << std::endl;
    GameUtils::Console::resetColor();
    
    player.takeDamage(totalDamage);
}

void CombatSystem::displayCombatStatus(const Player& player, const Enemy& enemy) {
    GameUtils::Console::setColor(GameUtils::ConsoleColor::CYAN);
    std::cout << "\n--- Combat Status ---" << std::endl;
    std::cout << player.getName() << ": ";
    GameUtils::Art::displayHealthBar(player.getHP(), player.getMaxHP());
    
    GameUtils::Console::setColor(GameUtils::ConsoleColor::RED);
    std::cout << enemy.getName() << ": ";
    GameUtils::Art::displayHealthBar(enemy.getHP(), enemy.getMaxHP());
    GameUtils::Console::resetColor();
}

int CombatSystem::calculateDamage(int attack, int defense) {
    int damage = attack - defense;
    return GameUtils::Utils::clamp(damage, 1, attack);
}

bool CombatSystem::isCombatOver(const Player& player, const Enemy& enemy) {
    return player.getHP() <= 0 || !enemy.isAlive();
}

} // namespace GameCore
