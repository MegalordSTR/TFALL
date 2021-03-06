#pragma once

#include "MW/Core/SharedContext.hpp"
#include "MW/Core/StateManager.hpp"
#include "MW/Resources/ResourceHolder.hpp"
#include "MW/Resources/ResourceIdentifiers.hpp"
#include "MW/Resources/SoundPlayer.hpp"
#include "MW/Core/InputManager.hpp"

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

    void closeWindow(MW::EventDetails* details);

private:
    float targetFPS;
    sf::Time timePerFrame;
    sf::RenderWindow window;

    MW::InputManager inputManager;

    MW::FontHolder fontHolder;
    MW::TextureHolder textureHolder;
    MW::SoundPlayer soundPlayer;

    std::shared_ptr<MW::SharedContext> ctx;

    std::shared_ptr<MW::StateManager> stateManager;
};
