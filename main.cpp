#include <iostream>
#include <memory>
#include <vector>
#include <random>
#include <ctime>
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "GameUtils.h"
#include "CombatSystem.h"

using namespace GameCore;
using namespace GameUtils;

// Template function for displaying game messages
template<typename T>
void displayMessage(const T& message) {
    std::cout << message << std::endl;
}

// Function demonstrating reference usage
void displayPlayerStats(const Player& player) {
    Console::setColor(ConsoleColor::CYAN);
    std::cout << "\n=== PLAYER STATS ===" << std::endl;
    std::cout << "Name: " << player.getName() << std::endl;
    std::cout << "HP: " << player.getHP() << "/" << player.getMaxHP() << std::endl;
    std::cout << "Attack: " << player.getAttack() << std::endl;
    std::cout << "Defense: " << player.getDefense() << std::endl;
    std::cout << "Level: " << player.getLevel() << std::endl;
    std::cout << "XP: " << player.getXP() << "/" << player.getXPToNextLevel() << std::endl;
    Console::resetColor();
}

// Function demonstrating unique_ptr usage
std::unique_ptr<Enemy> createEnemy(EnemyType type, int level) {
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

// Game loop
void gameLoop() {
    // Display title screen
    Console::setColor(ConsoleColor::YELLOW);
    Art::displayTitle();
    Console::resetColor();
    
    std::cout << "\nWelcome to the C++ RPG Adventure!" << std::endl;
    std::cout << "Press Enter to start...";
    std::cin.ignore();
    
    // Create player using unique_ptr
    auto player = std::make_unique<Player>("Hero", 100, 15, 5);
    
    // Give player starting items using shared_ptr
    auto healthPotion = std::make_shared<HealthPotion>("Health Potion", 30);
    auto sword = std::make_shared<Weapon>("Iron Sword", 10, WeaponType::SWORD);
    
    player->addItem(healthPotion);
    player->addItem(sword);
    
    // Game state enum
    GameState state = GameState::EXPLORING;
    
    // Random number generator
    std::mt19937 rng(static_cast<unsigned int>(time(nullptr)));
    std::uniform_int_distribution<int> enemyDist(0, 2);
    std::uniform_int_distribution<int> actionDist(1, 100);
    
    while (state != GameState::GAME_OVER) {
        Console::clearScreen();
        
        switch(state) {
            case GameState::EXPLORING: {
                Console::setColor(ConsoleColor::GREEN);
                std::cout << "\nYou are exploring the dungeon..." << std::endl;
                Console::resetColor();
                
                displayPlayerStats(*player);
                player->displayEquipment();
                
                std::cout << "\nWhat do you want to do?" << std::endl;
                std::cout << "1. Continue exploring" << std::endl;
                std::cout << "2. View inventory" << std::endl;
                std::cout << "3. Use item" << std::endl;
                std::cout << "4. Quit game" << std::endl;
                
                int choice;
                std::cout << "\nChoice: ";
                std::cin >> choice;
                
                if (choice == 1) {
                    // Random encounter
                    if (actionDist(rng) <= 60) {
                        EnemyType enemyType = static_cast<EnemyType>(enemyDist(rng));
                        auto enemy = createEnemy(enemyType, player->getLevel());
                        
                        Console::setColor(ConsoleColor::RED);
                        std::cout << "\nA " << enemy->getName() << " appears!" << std::endl;
                        Console::resetColor();
                        
                        state = GameState::COMBAT;
                    } else {
                        Console::setColor(ConsoleColor::BLUE);
                        std::cout << "\nYou found a peaceful area. Nothing happens." << std::endl;
                        Console::resetColor();
                        std::cout << "Press Enter to continue...";
                        std::cin.ignore();
                        std::cin.ignore();
                    }
                } else if (choice == 2) {
                    player->displayInventory();
                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore();
                    std::cin.ignore();
                } else if (choice == 3) {
                    player->displayInventory();
                    std::cout << "\nEnter item number to use (0 to cancel): ";
                    int itemNum;
                    std::cin >> itemNum;
                    
                    if (itemNum > 0) {
                        player->useItem(itemNum - 1);
                    }
                    std::cout << "Press Enter to continue...";
                    std::cin.ignore();
                    std::cin.ignore();
                } else if (choice == 4) {
                    state = GameState::GAME_OVER;
                }
                break;
            }
            
            case GameState::COMBAT: {
                // Create enemy for combat
                EnemyType enemyType = static_cast<EnemyType>(enemyDist(rng));
                auto enemy = createEnemy(enemyType, player->getLevel());
                
                CombatSystem::battle(*player, *enemy);
                
                if (player->getHP() <= 0) {
                    Console::setColor(ConsoleColor::RED);
                    std::cout << "\nYOU DIED!" << std::endl;
                    Console::resetColor();
                    state = GameState::GAME_OVER;
                } else {
                    // Grant XP and loot
                    int xpGained = enemy->getXPValue();
                    player->gainXP(xpGained);
                    
                    Console::setColor(ConsoleColor::GREEN);
                    std::cout << "\nYou gained " << xpGained << " XP!" << std::endl;
                    Console::resetColor();
                    
                    // Random item drop
                    if (actionDist(rng) <= 40) {
                        auto newItem = ItemFactory::createRandomItem(player->getLevel());
                        player->addItem(newItem);
                        Console::setColor(ConsoleColor::YELLOW);
                        std::cout << "You found: " << newItem->getName() << "!" << std::endl;
                        Console::resetColor();
                    }
                    
                    state = GameState::EXPLORING;
                    std::cout << "Press Enter to continue...";
                    std::cin.ignore();
                    std::cin.ignore();
                }
                break;
            }
            
            default:
                state = GameState::EXPLORING;
                break;
        }
    }
    
    Console::setColor(ConsoleColor::YELLOW);
    Art::displayGameOver();
    Console::resetColor();
    
    std::cout << "\nThanks for playing!" << std::endl;
    std::cout << "Final Level: " << player->getLevel() << std::endl;
}

int main() {
    try {
        gameLoop();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
