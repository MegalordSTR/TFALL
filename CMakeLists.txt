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
        Frameworks/Engine/Node/SceneNode.cpp
        Frameworks/Engine/Node/SceneNode.hpp
        Frameworks/Engine/Resources/FontConsts.hpp
        Frameworks/Engine/Resources/ResourceIdentifiers.hpp
        Frameworks/Engine/Resources/ResourceHolder.hpp
        Frameworks/Engine/Utility/Utility.cpp
        Frameworks/Engine/Utility/Utility.h
        Frameworks/Engine/Node/CategoryIdentifiers.hpp
        Frameworks/Engine/Node/SceneManager.cpp
        Frameworks/Engine/Node/SceneManager.hpp
        Frameworks/Engine/Node/SoundNode.cpp
        Frameworks/Engine/Node/SoundNode.hpp
        Frameworks/Engine/Node/TextNode.cpp
        Frameworks/Engine/Node/TextNode.hpp
        Frameworks/Engine/Resources/SoundPlayer.cpp
        Frameworks/Engine/Resources/SoundPlayer.hpp
        Frameworks/Engine/Command/Command.cpp
        Frameworks/Engine/Command/Command.hpp
        Frameworks/Engine/Command/CommandQueue.cpp
        Frameworks/Engine/Command/CommandQueue.hpp
        Frameworks/Engine/State/State.cpp
        Frameworks/Engine/State/State.hpp
        Frameworks/Engine/State/StateIdentifiers.hpp
        Frameworks/Engine/State/StateStack.cpp
        Frameworks/Engine/State/StateStack.hpp
        src/App.cpp
        src/App.hpp
        src/States/GameState.cpp
        src/States/GameState.hpp
        src/Game/World.cpp src/Game/World.hpp src/Game/Grid.cpp src/Game/Grid.hpp src/Game/Block.cpp src/Game/Block.hpp src/Game/Figure.cpp src/Game/Figure.hpp)

# SFML
target_link_libraries(TFALL sfml-system sfml-window sfml-graphics sfml-network sfml-audio)