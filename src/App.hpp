//
// Created by Admin on 17.03.2022.
//

#ifndef TFALL_APP_HPP
#define TFALL_APP_HPP
#include "Engine/State/StateStack.hpp"
#include "Engine/Resources/ResourceHolder.hpp"
#include "Engine/Resources/ResourceIdentifiers.hpp"
#include "Engine/Resources/SoundPlayer.hpp"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class App {

public:
    App(int windowWidth, int windowHeight, float targetFPS);

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

#endif //TFALL_APP_HPP
