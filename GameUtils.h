#ifndef GAMEUTILS_H
#define GAMEUTILS_H

#include <string>
#include <iostream>

namespace GameUtils {

// Enum for console colors (cross-platform)
enum class ConsoleColor {
    RESET,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
    BOLD_RED,
    BOLD_GREEN,
    BOLD_YELLOW,
    BOLD_BLUE,
    BOLD_MAGENTA,
    BOLD_CYAN,
    BOLD_WHITE
};

// Enum for game states
enum class GameState {
    EXPLORING,
    COMBAT,
    INVENTORY,
    GAME_OVER,
    VICTORY
};

// Console utility class for color output and screen clearing
class Console {
public:
    // Set console color
    static void setColor(ConsoleColor color);
    
    // Reset console color
    static void resetColor();
    
    // Clear screen (cross-platform)
    static void clearScreen();
    
    // Pause execution
    static void pause();
    
    // Get user input with validation
    template<typename T>
    static T getInput(const std::string& prompt) {
        T value;
        std::cout << prompt;
        std::cin >> value;
        return value;
    }
};

// ASCII Art class for visual elements
class Art {
public:
    // Display title screen
    static void displayTitle();
    
    // Display game over screen
    static void displayGameOver();
    
    // Display victory screen
    static void displayVictory();
    
    // Display separator line
    static void displaySeparator();
    
    // Display health bar
    static void displayHealthBar(int current, int maximum, int width = 20);
};

// Utility functions
class Utils {
public:
    // Generate random number in range
    static int randomInt(int min, int max);
    
    // Generate random float in range
    static float randomFloat(float min, float max);
    
    // Clamp value between min and max
    template<typename T>
    static T clamp(T value, T min, T max) {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }
    
    // String formatting helper
    static std::string formatString(const std::string& format, ...);
};

// Logger class for debugging
class Logger {
public:
    enum class LogLevel {
        DEBUG,
        INFO,
        WARNING,
        ERR
    };
    
    static void log(LogLevel level, const std::string& message);
    static void debug(const std::string& message);
    static void info(const std::string& message);
    static void warning(const std::string& message);
    static void error(const std::string& message);
};

} // namespace GameUtils

#endif // GAMEUTILS_H
