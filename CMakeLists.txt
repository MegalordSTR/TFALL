cmake_minimum_required(VERSION 3.21)
project(TFALL)

set(CMAKE_CXX_STANDARD 17)

set(STD_INCLUDE_DIRECTORIES ./include ./src ./Frameworks)
include_directories(${STD_INCLUDE_DIRECTORIES})

## In most cases better set in the CMake cache
set(SFML_DIR "./library/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
add_executable(TFALL
        src/main.cpp
        Frameworks/MW/Node/SceneNode.cpp
        Frameworks/MW/Node/SceneNode.hpp
        Frameworks/MW/Resources/FontConsts.hpp
        Frameworks/MW/Resources/ResourceIdentifiers.hpp
        Frameworks/MW/Resources/ResourceHolder.hpp
        Frameworks/MW/Utility/Utility.cpp
        Frameworks/MW/Utility/Utility.h
        Frameworks/MW/Node/CategoryIdentifiers.hpp
        Frameworks/MW/Node/SceneManager.cpp
        Frameworks/MW/Node/SceneManager.hpp
        Frameworks/MW/Node/SoundNode.cpp
        Frameworks/MW/Node/SoundNode.hpp
        Frameworks/MW/Node/TextNode.cpp
        Frameworks/MW/Node/TextNode.hpp
        Frameworks/MW/Resources/SoundPlayer.cpp
        Frameworks/MW/Resources/SoundPlayer.hpp
        Frameworks/MW/Command/Command.cpp
        Frameworks/MW/Command/Command.hpp
        Frameworks/MW/Command/CommandQueue.cpp
        Frameworks/MW/Command/CommandQueue.hpp
        Frameworks/MW/State/State.cpp
        Frameworks/MW/State/State.hpp
        Frameworks/MW/State/StateIdentifiers.hpp
        Frameworks/MW/State/StateStack.cpp
        Frameworks/MW/State/StateStack.hpp
        src/App.cpp
        src/App.hpp
        src/States/GameState.cpp
        src/States/GameState.hpp
        src/Game/World.cpp
        src/Game/World.hpp
        src/Game/GridSpriteNode.cpp
        src/Game/GridSpriteNode.hpp
        Frameworks/MW/Core/InputManager.cpp
        Frameworks/MW/Core/InputManager.hpp
        src/Game/TetrisGrid.cpp
        src/Game/TetrisGrid.hpp
        Frameworks/MW/Core/Mwtype.hpp
        src/Game/TetrisGridSettings.hpp
        Frameworks/MW/Node/RectangleShapeNode.cpp
        Frameworks/MW/Node/RectangleShapeNode.hpp
        Frameworks/MW/Node/SpriteNode.cpp
        Frameworks/MW/Node/SpriteNode.hpp
        Frameworks/MW/Node/Label.cpp
        Frameworks/MW/Node/Label.hpp
        Frameworks/MW/Core/StateManager.cpp
        Frameworks/MW/Core/StateManager.hpp
        Frameworks/MW/Core/SharedContext.hpp)

# SFML
target_link_libraries(TFALL sfml-system sfml-window sfml-graphics sfml-network sfml-audio)