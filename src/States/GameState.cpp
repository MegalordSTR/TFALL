//
// Created by Admin on 18.03.2022.
//

#include "GameState.hpp"

GameState::GameState(MW::StateStack &stack, const MW::State::Context &ctx) :
    State(stack, ctx),
    world(*ctx.window, *ctx.soundPlayer, *ctx.textures)
{
    tickTime = sf::seconds(0.5f);
}

GameState::~GameState() {

}

void GameState::draw() {
    world.draw();
}

bool GameState::update(sf::Time dt) {
    timeElapsed += dt;
    if (timeElapsed > tickTime)
    {
        timeElapsed -= tickTime;
        world.update(tickTime);
    }

    return true;
}

// TODO: подумать что вообще делать тут
bool GameState::handleEvent(const sf::Event &event) {
//    player.handleInputEvents(event, world.getCommandQueue());
    return true;
}



