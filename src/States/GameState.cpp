#include "GameState.hpp"

GameState::GameState(MW::StateStack &stack, const MW::State::Context &ctx) :
    State(stack, ctx),
    world(*ctx.window, *ctx.soundPlayer, *ctx.textures, *ctx.fonts, *ctx.inputManager)
{
    tickTime = 0.35f;
}

GameState::~GameState() {
    getContext().soundPlayer->stopAndRemoveAll();
}

void GameState::draw() {
    world.draw();
}

bool GameState::update(sf::Time dt) {
    timeElapsed += dt;

    auto moddedTickTime = sf::seconds(tickTime * static_cast<float>((1 - static_cast<float>(world.GetScore()) / 100)));
    if (timeElapsed > moddedTickTime)
    {
        timeElapsed -= moddedTickTime;
        world.update(moddedTickTime);
    }

    if (!world.CheckSpace())
    {
        requestStateClear();
        requestStackPush(MW::States::ID::Game);
    }



    return true;
}

// TODO: подумать что вообще делать тут
bool GameState::handleEvent(const sf::Event &event) {
//    player.handleInputEvents(event, world.getCommandQueue());
    return true;
}
