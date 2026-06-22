#include "GameUtils.h"
#include <iostream>
#include <random>
#include <cstdarg>
#include <chrono>
#include <thread>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

namespace GameUtils {

// Console implementation
void Console::setColor(ConsoleColor color) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorCode;
    
    switch(color) {
        case ConsoleColor::RESET: colorCode = 7; break;
        case ConsoleColor::RED: colorCode = 4; break;
        case ConsoleColor::GREEN: colorCode = 2; break;
        case ConsoleColor::YELLOW: colorCode = 6; break;
        case ConsoleColor::BLUE: colorCode = 1; break;
        case ConsoleColor::MAGENTA: colorCode = 5; break;
        case ConsoleColor::CYAN: colorCode = 3; break;
        case ConsoleColor::WHITE: colorCode = 7; break;
        case ConsoleColor::BOLD_RED: colorCode = 12; break;
        case ConsoleColor::BOLD_GREEN: colorCode = 10; break;
        case ConsoleColor::BOLD_YELLOW: colorCode = 14; break;
        case ConsoleColor::BOLD_BLUE: colorCode = 9; break;
        case ConsoleColor::BOLD_MAGENTA: colorCode = 13; break;
        case ConsoleColor::BOLD_CYAN: colorCode = 11; break;
        case ConsoleColor::BOLD_WHITE: colorCode = 15; break;
        default: colorCode = 7; break;
    }
    
    SetConsoleTextAttribute(hConsole, colorCode);
#else
    std::string colorCode;
    switch(color) {
        case ConsoleColor::RESET: colorCode = "\033[0m"; break;
        case ConsoleColor::RED: colorCode = "\033[31m"; break;
        case ConsoleColor::GREEN: colorCode = "\033[32m"; break;
        case ConsoleColor::YELLOW: colorCode = "\033[33m"; break;
        case ConsoleColor::BLUE: colorCode = "\033[34m"; break;
        case ConsoleColor::MAGENTA: colorCode = "\033[35m"; break;
        case ConsoleColor::CYAN: colorCode = "\033[36m"; break;
        case ConsoleColor::WHITE: colorCode = "\033[37m"; break;
        case ConsoleColor::BOLD_RED: colorCode = "\033[1;31m"; break;
        case ConsoleColor::BOLD_GREEN: colorCode = "\033[1;32m"; break;
        case ConsoleColor::BOLD_YELLOW: colorCode = "\033[1;33m"; break;
        case ConsoleColor::BOLD_BLUE: colorCode = "\033[1;34m"; break;
        case ConsoleColor::BOLD_MAGENTA: colorCode = "\033[1;35m"; break;
        case ConsoleColor::BOLD_CYAN: colorCode = "\033[1;36m"; break;
        case ConsoleColor::BOLD_WHITE: colorCode = "\033[1;37m"; break;
        default: colorCode = "\033[0m"; break;
    }
    std::cout << colorCode;
#endif
}

void Console::resetColor() {
    setColor(ConsoleColor::RESET);
}

void Console::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Console::pause() {
    std::cout << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

// Art implementation
void Art::displayTitle() {
    std::cout << R"(
    ████████╗██╗   ██╗███╗   ██╗████████╗██╗   ██╗██╗██████╗ ███████╗
    ╚══██╔══╝██║   ██║████╗  ██║╚══██╔══╝██║   ██║██║██╔══██╗██╔════╝
       ██║   ██║   ██║██╔██╗ ██║   ██║   ██║   ██║██║██║  ██║███████╗
       ██║   ██║   ██║██║╚██╗██║   ██║   ██║   ██║██║██║  ██║╚════██║
       ██║   ╚██████╔╝██║ ╚████║   ██║   ╚██████╔╝██║██████╔╝███████║
       ╚═╝    ╚═════╝ ╚═╝  ╚═══╝   ╚═╝    ╚═════╝ ╚═╝╚═════╝ ╚══════╝
                    ████████╗███████╗██████╗ ███╗   ███╗
                    ╚══██╔══╝██╔════╝██╔══██╗████╗ ████║
                       ██║   █████╗  ██████╔╝██╔████╔██║
                       ██║   ██╔══╝  ██╔══██╗██║╚██╔╝██║
                       ██║   ███████╗██║  ██║██║ ╚═╝ ██║
                       ╚═╝   ╚══════╝╚═╝  ╚═╝╚═╝     ╚═╝
)" << std::endl;
}

void Art::displayGameOver() {
    std::cout << R"(
   ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██████╗ ███╗   ██╗███████╗███╗   ██╗████████╗
  ██╔════╝██╔══██╗████╗ ████║██╔════╝    ██╔════╝██╔═══██╗████╗  ██║██╔════╝████╗  ██║╚══██╔══╝
  ██║     ███████║██╔████╔██║███████╗    ██║     ██║   ██║██╔██╗ ██║█████╗  ██╔██╗ ██║   ██║
  ██║     ██╔══██║██║╚██╔╝██║╚════██║    ██║     ██║   ██║██║╚██╗██║██╔══╝  ██║╚██╗██║   ██║
  ╚██████╗██║  ██║██║ ╚═╝ ██║███████║    ╚██████╗╚██████╔╝██║ ╚████║███████╗██║ ╚████║   ██║
   ╚═════╝╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝╚═╝  ╚═══╝   ╚═╝
)" << std::endl;
}

void Art::displayVictory() {
    std::cout << R"(
  ███████╗ ██████╗ ██╗     ██╗     ███████╗ ██████╗██████╗ ███████╗███████╗
  ██╔════╝██╔═══██╗██║     ██║     ██╔════╝██╔════╝██╔══██╗██╔════╝██╔════╝
  █████╗  ██║   ██║██║     ██║     █████╗  ██║     ██████╔╝█████╗  ███████╗
  ██╔══╝  ██║   ██║██║     ██║     ██╔══╝  ██║     ██╔══██╗██╔══╝  ╚════██║
  ██║     ╚██████╔╝███████╗███████╗███████╗╚██████╗██║  ██║███████╗███████║
  ╚═╝      ╚═════╝ ╚══════╝╚══════╝╚══════╝ ╚═════╝╚═╝  ╚═╝╚══════╝╚══════╝
)" << std::endl;
}

void Art::displaySeparator() {
    std::cout << "==================================================" << std::endl;
}

void Art::displayHealthBar(int current, int maximum, int width) {
    float percentage = static_cast<float>(current) / maximum;
    int filled = static_cast<int>(percentage * width);
    int empty = width - filled;
    
    std::cout << "[";
    for (int i = 0; i < filled; ++i) {
        std::cout << "█";
    }
    for (int i = 0; i < empty; ++i) {
        std::cout << " ";
    }
    std::cout << "] " << current << "/" << maximum << std::endl;
}

// Utils implementation
int Utils::randomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

float Utils::randomFloat(float min, float max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

std::string Utils::formatString(const std::string& format, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format.c_str(), args);
    va_end(args);
    return std::string(buffer);
}

// Logger implementation
void Logger::log(LogLevel level, const std::string& message) {
    std::string levelStr;
    ConsoleColor color;
    
    switch(level) {
        case LogLevel::DEBUG:
            levelStr = "DEBUG";
            color = ConsoleColor::CYAN;
            break;
        case LogLevel::INFO:
            levelStr = "INFO";
            color = ConsoleColor::GREEN;
            break;
        case LogLevel::WARNING:
            levelStr = "WARNING";
            color = ConsoleColor::YELLOW;
            break;
        case LogLevel::ERR:
            levelStr = "ERROR";
            color = ConsoleColor::RED;
            break;
    }
    
    Console::setColor(color);
    std::cout << "[" << levelStr << "] " << message << std::endl;
    Console::resetColor();
}

void Logger::debug(const std::string& message) {
    log(LogLevel::DEBUG, message);
}

void Logger::info(const std::string& message) {
    log(LogLevel::INFO, message);
}

void Logger::warning(const std::string& message) {
    log(LogLevel::WARNING, message);
}

void Logger::error(const std::string& message) {
    log(LogLevel::ERR, message);
}

} // namespace GameUtils
