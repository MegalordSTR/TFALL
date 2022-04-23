#pragma once

#include <Game/World.hpp>

#include "MW/State/State.hpp"

class GameState : public MW::State {
public:
    GameState(MW::StateStack &stack, const Context &ctx);

public:

    void draw() override;

    bool update(sf::Time dt) override;

    bool handleEvent(const sf::Event &event) override;

private:
    ~GameState() override;

private:
    World world;
    sf::Time timeElapsed;
    float tickTime;
};
