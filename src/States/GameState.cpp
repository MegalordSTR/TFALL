#include "GameState.hpp"
#include <MW/Core/StateManager.hpp>

GameState::GameState(MW::StateManager* l_stateManager) :
        MW::BaseState(l_stateManager),
        tickTime(0.25f),
        world(nullptr)
{
}


void GameState::OnCreate() {
    auto &ctx = *m_stateMgr->GetContext();
    world = std::make_unique<World>(*ctx.window, *ctx.soundPlayer, *ctx.textures, *ctx.fonts, *ctx.inputManager);
    ctx.inputManager->AddCallback<GameState>(MW::StateType::Game, "toggle_world_debug", &GameState::toggleDebug, this);
}

void GameState::OnDestroy() {
    auto &ctx = *m_stateMgr->GetContext();
    ctx.soundPlayer->stopAndRemoveAll();
    ctx.inputManager->RemoveCallback(MW::StateType::Game, "toggle_world_debug");
}

void GameState::Activate() {

}

void GameState::Deactivate() {

}

void GameState::Update(const sf::Time &dt) {
    timeElapsed += dt;

    auto moddedTickTime = sf::seconds(tickTime * static_cast<float>((1 - static_cast<float>(world->GetScore()) / 100)));
    if (timeElapsed > moddedTickTime)
    {
        timeElapsed -= moddedTickTime;
        world->update(moddedTickTime);
    }

    if (!world->CheckSpace())
    {
        OnDestroy();
        auto &ctx = *m_stateMgr->GetContext();
        world = std::make_unique<World>(*ctx.window, *ctx.soundPlayer, *ctx.textures, *ctx.fonts, *ctx.inputManager);
    }
}

void GameState::Draw() {
    world->draw();
}

void GameState::toggleDebug(MW::EventDetails* eventDetails) {
    world->ToggleDebug();
}
