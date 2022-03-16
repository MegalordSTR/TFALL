cmake_minimum_required(VERSION 3.21)
project(TFALL)

set(CMAKE_CXX_STANDARD 17)

set(STD_INCLUDE_DIRECTORIES ./include ./src ./Engine)
include_directories(${STD_INCLUDE_DIRECTORIES})

## In most cases better set in the CMake cache
set(SFML_DIR "./library/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
add_executable(TFALL
        src/main.cpp
        Engine/Node/SceneNode.cpp
        Engine/Node/SceneNode.h
        Engine/Resources/FontConsts.h
        Engine/Resources/ResourceIdentifiers.h
        Engine/Resources/ResourceHolder.h
        Engine/Utility/Utility.cpp
        Engine/Utility/Utility.h
        Engine/Node/CategoryIdentifiers.h
        Engine/Node/SceneManager.cpp
        Engine/Node/SceneManager.h
        Engine/Node/SoundNode.cpp
        Engine/Node/SoundNode.h
        Engine/Node/TextNode.cpp
        Engine/Node/TextNode.h
        Engine/Resources/SoundPlayer.cpp
        Engine/Resources/SoundPlayer.h
        Engine/Command/Command.cpp
        Engine/Command/Command.h
        Engine/Command/CommandQueue.cpp
        Engine/Command/CommandQueue.h
        Engine/State/State.cpp
        Engine/State/State.h
        Engine/State/StateIdentifiers.h
        Engine/State/StateStack.cpp
        Engine/State/StateStack.h)

# SFML
target_link_libraries(TFALL sfml-system sfml-window sfml-graphics sfml-network sfml-audio)