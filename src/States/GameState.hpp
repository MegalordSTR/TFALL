#pragma once

#include <Game/World.hpp>

#include <MW/Core/InputManager.hpp>
#include <MW/Core/BaseState.hpp>

class GameState : public MW::BaseState {
public:
    explicit GameState(MW::StateManager* l_StateManager);

public:
    void OnCreate() override;

    void OnDestroy() override;

    void Activate() override;

    void Deactivate() override;

    void Update(const sf::Time &dt) override;

    void Draw() override;

private:
    void toggleDebug(MW::EventDetails* eventDetails);

private:
    std::unique_ptr<World> world;
    sf::Time timeElapsed;
    float tickTime;
};
