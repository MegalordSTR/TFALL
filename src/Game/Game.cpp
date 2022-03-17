//
// Created by Admin on 17.03.2022.
//

#include "Game.h"

Game::Game(int windowWidth, int windowHeight, float targetFPS) :
        window(sf::VideoMode(windowWidth, windowHeight), "Game", sf::Style::Close),
        targetFPS(targetFPS),
        timePerFrame(sf::seconds(1 / targetFPS)),
        fontHolder(),
        textureHolder(),
        soundPlayer(),
        states(Engine::State::Context(window, fontHolder, textureHolder, soundPlayer))
{

}

void Game::Run() {
    sf::Clock clock;
    sf::Time timeElapsed = sf::Time::Zero;
    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        timeElapsed += dt;
        while (timeElapsed > timePerFrame)
        {
            timeElapsed -= dt;
            handleInput();
            update(timePerFrame);
        }

        render();
    }
}

void Game::handleInput() {
    sf::Event event{};
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            window.close();

        states.handleEvent(event);
    }
}

void Game::update(sf::Time dt) {
    states.update(dt);
}

void Game::render() {
    states.draw();
}
