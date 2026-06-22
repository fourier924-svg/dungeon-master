#ifndef COMBATSYSTEM_H
#define COMBATSYSTEM_H

#include "Player.h"
#include "Enemy.h"
#include <memory>

namespace GameCore {

// CombatSystem class - demonstrates references and const correctness
class CombatSystem {
public:
    // Battle function using references (no copying)
    static void battle(Player& player, Enemy& enemy);
    
    // Player attack function
    static void playerAttack(Player& player, Enemy& enemy);
    
    // Enemy attack function
    static void enemyAttack(const Enemy& enemy, Player& player);
    
    // Display combat status
    static void displayCombatStatus(const Player& player, const Enemy& enemy);
    
    // Calculate damage with const correctness
    static int calculateDamage(int attack, int defense);
    
    // Check if combat should end
    static bool isCombatOver(const Player& player, const Enemy& enemy);
    
private:
    // Private constructor - static class
    CombatSystem() = default;
};

} // namespace GameCore

#endif // COMBATSYSTEM_H
