# C++ RPG Game

A text-based RPG game built with modern C++ (C++17) that demonstrates essential C++ concepts including smart pointers, templates, namespaces, references, enums, polymorphism, and more.

## Features

### C++ Concepts Demonstrated

- **Smart Pointers**: `std::unique_ptr` for enemy management, `std::shared_ptr` for inventory items
- **Templates**: `StackableItem<T>` template class for stackable game items
- **Namespaces**: `GameCore` and `GameUtils` namespaces for code organization
- **References**: Pass-by-reference in combat system and player functions
- **Enums**: `EnemyType`, `ItemType`, `WeaponType`, `GameState`, `ConsoleColor`
- **Polymorphism**: Abstract `Enemy` base class with derived `Goblin`, `Orc`, and `Dragon` classes
- **Const Correctness**: Const member functions and const references throughout
- **Rule of Five**: Copy/move constructors and assignment operators in Player class
- **Operator Overloading**: `operator==` and `operator<<` in Player class
- **Factory Pattern**: `ItemFactory` and `Enemy::createEnemy()` for object creation
- **Virtual Functions**: Pure virtual and virtual functions for polymorphic behavior
- **RAII**: Resource management through smart pointers and destructors

### Game Features

- **Player System**: Create and customize your hero with HP, attack, defense, and leveling
- **Combat System**: Turn-based combat with attack, item usage, and escape options
- **Enemy Variety**: Three enemy types (Goblin, Orc, Dragon) with unique abilities and ASCII art
- **Inventory System**: Collect and use items including health potions, weapons, and armor
- **Visual Elements**: ASCII art for enemies, title screen, and game over screen
- **Color Output**: Cross-platform console color support for enhanced visuals
- **Leveling System**: Gain XP from battles and level up with stat increases

## Compilation

### Using CMake (Recommended)

```bash
# Create build directory
mkdir build
cd build

# Generate build files
cmake ..

# Build the project
cmake --build .

# Run the game
./CppRPGGame  # On Linux/Mac
CppRPGGame.exe  # On Windows
```

### Using g++ (Linux/Mac)

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -o CppRPGGame \
    main.cpp \
    Player.cpp \
    Enemy.cpp \
    Item.cpp \
    GameUtils.cpp \
    CombatSystem.cpp

./CppRPGGame
```

### Using Visual Studio (Windows)

1. Open Visual Studio
2. Create a new "Empty Project"
3. Add all `.cpp` and `.h` files to the project
4. Set C++ Language Standard to C++17 in Project Properties
5. Build and Run

### Using clang++ (Linux/Mac)

```bash
clang++ -std=c++17 -Wall -Wextra -pedantic -o CppRPGGame \
    main.cpp \
    Player.cpp \
    Enemy.cpp \
    Item.cpp \
    GameUtils.cpp \
    CombatSystem.cpp

./CppRPGGame
```

## How to Play

1. Run the executable
2. Press Enter to start the game
3. Choose actions from the menu:
   - **Explore**: Wander the dungeon and encounter enemies
   - **View Inventory**: Check your collected items
   - **Use Item**: Consume potions or equip gear
   - **Quit**: Exit the game
4. In combat:
   - **Attack**: Deal damage to the enemy
   - **Use Item**: Use items from your inventory
   - **Run**: Attempt to flee (30% success rate)
5. Defeat enemies to gain XP and find items
6. Level up to increase your stats

## Project Structure

```
Game/
├── main.cpp              # Game loop and main entry point
├── Player.h/cpp          # Player class with attributes and inventory
├── Enemy.h/cpp           # Enemy class hierarchy with polymorphism
├── Item.h/cpp            # Item system with templates and smart pointers
├── GameUtils.h/cpp       # Utility functions, console I/O, ASCII art
├── CombatSystem.h/cpp    # Combat mechanics with references
├── CMakeLists.txt        # CMake build configuration
└── README.md             # This file
```

## Code Highlights

### Smart Pointers
```cpp
// unique_ptr for exclusive ownership
auto enemy = std::make_unique<Goblin>(level);

// shared_ptr for shared ownership (inventory)
auto healthPotion = std::make_shared<HealthPotion>("Health Potion", 30);
player->addItem(healthPotion);
```

### Templates
```cpp
template<typename T>
class StackableItem : public Item {
    // Generic stackable item implementation
};
```

### Polymorphism
```cpp
// Abstract base class
class Enemy {
    virtual void specialAbility() = 0;  // Pure virtual
    virtual void display() const;       // Virtual with default
};

// Derived classes override virtual functions
class Goblin : public Enemy {
    void specialAbility() override;
    void display() const override;
};
```

### References and Const Correctness
```cpp
void playerAttack(Player& player, Enemy& enemy);  // Pass by reference
void displayCombatStatus(const Player& player, const Enemy& enemy);  // Const references
```

## Requirements

- C++17 compatible compiler (g++ 7+, clang++ 5+, MSVC 2017+)
- CMake 3.10+ (optional, for CMake build)
- Windows, Linux, or macOS

## License

This is an educational project for learning C++ concepts. Feel free to use and modify as needed.
