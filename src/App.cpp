//
// Created by Admin on 17.03.2022.
//

#include "App.hpp"
#include "Engine/State/StateIdentifiers.hpp"
#include "States/GameState.hpp"

App::App(int windowWidth, int windowHeight, float targetFPS) :
        window(sf::VideoMode(windowWidth, windowHeight), "App", sf::Style::Close),
        targetFPS(targetFPS),
        timePerFrame(sf::seconds(1 / targetFPS)),
        fontHolder(),
        textureHolder(),
        soundPlayer(),
        states(Engine::State::Context(window, fontHolder, textureHolder, soundPlayer))
{
    textureHolder.load(Engine::Resources::Texture::Block, "blocks.png");

    states.registerState<GameState>(Engine::States::ID::Game);

    states.pushState(Engine::States::ID::Game);
}

void App::Run() {
    sf::Clock clock;
    sf::Time timeElapsed = sf::Time::Zero;
    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        timeElapsed += dt;
        while (timeElapsed > timePerFrame)
        {
            timeElapsed -= timePerFrame;
            handleInput();
            update(timePerFrame);
        }

        render();
    }
}

void App::handleInput() {
    sf::Event event{};
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            window.close();

        states.handleEvent(event);
    }
}

void App::update(sf::Time dt) {
    states.update(dt);
}

void App::render() {
    window.clear(sf::Color::White);
    states.draw();
    window.display();
}
