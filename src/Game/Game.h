//
// Created by Admin on 17.03.2022.
//

#ifndef TFALL_GAME_H
#define TFALL_GAME_H
#include "State/StateStack.h"
#include <Resources/ResourceHolder.h>
#include <Resources/ResourceIdentifiers.h>
#include <Resources/SoundPlayer.h>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Game {

public:
    Game(int windowWidth, int windowHeight, float targetFPS);

    void Run();

private:
    void handleInput();
    void update(sf::Time dt);
    void render();

private:
    float targetFPS;
    sf::Time timePerFrame;
    sf::RenderWindow window;

    Engine::FontHolder fontHolder;
    Engine::TextureHolder textureHolder;
    Engine::SoundPlayer soundPlayer;

    Engine::StateStack states;
};

#endif //TFALL_GAME_H
