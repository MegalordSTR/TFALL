//
// Created by Admin on 18.03.2022.
//

#ifndef TFALL_GAMESTATE_HPP
#define TFALL_GAMESTATE_HPP

#include <Game/World.hpp>

#include "Engine/State/State.hpp"

class GameState : public Engine::State {
public:
    GameState(Engine::StateStack &stack, const Context &ctx);

public:

    void draw() override;

    bool update(sf::Time dt) override;

    bool handleEvent(const sf::Event &event) override;

private:
    ~GameState() override;

private:
    World world;
    sf::Time timeElapsed;
    sf::Time tickTime;
};

#endif //TFALL_GAMESTATE_HPP