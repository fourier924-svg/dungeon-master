cmake_minimum_required(VERSION 3.10)
project(CppRPGGame)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compiler warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Source files
set(SOURCES
    main.cpp
    Player.cpp
    Enemy.cpp
    Item.cpp
    GameUtils.cpp
    CombatSystem.cpp
)

# Header files
set(HEADERS
    Player.h
    Enemy.h
    Item.h
    GameUtils.h
    CombatSystem.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# For Windows, set subsystem to console
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE FALSE
    )
endif()
