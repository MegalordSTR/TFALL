#pragma once

#include <MW/Core/InputManager.hpp>
#include <MW/Core/StateManager.hpp>
#include <MW/Core/BaseState.hpp>

#include <MW/Node/RectangleShapeNode.hpp>
#include <MW/Node/Label.hpp>

using MW::Label;
using MW::RectangleShapeNode;

class MenuState : public MW::BaseState {
public:
    explicit MenuState(MW::StateManager* pManager);

    void OnCreate() override;

    void OnDestroy() override;

    void Activate() override;

    void Deactivate() override;

    void Update(const sf::Time &l_time) override;

    void Draw() override;

private:
    void onEnter(MW::EventDetails* eventDetails);

private:
    std::shared_ptr<Label> m_titleLabel;
    std::shared_ptr<Label> m_instructionsLabel;
    float m_alphaAccumulator;
};
