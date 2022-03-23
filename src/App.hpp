//
// Created by Admin on 17.03.2022.
//

#ifndef TFALL_APP_HPP
#define TFALL_APP_HPP
#include "MW/State/StateStack.hpp"
#include "MW/Resources/ResourceHolder.hpp"
#include "MW/Resources/ResourceIdentifiers.hpp"
#include "MW/Resources/SoundPlayer.hpp"

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

    MW::FontHolder fontHolder;
    MW::TextureHolder textureHolder;
    MW::SoundPlayer soundPlayer;

    MW::StateStack states;
};

#endif //TFALL_APP_HPP
