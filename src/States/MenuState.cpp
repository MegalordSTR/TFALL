#include "MenuState.hpp"
#include <MW/Resources/ResourceIdentifiers.hpp>
#include <MW/Resources/FontConsts.hpp>

#include <cmath>
#include <sstream>

MenuState::MenuState(MW::StateManager* pManager) :
        BaseState(pManager),
        m_alphaAccumulator(0.f)
{}

void MenuState::OnCreate()
{
    auto ctx = m_stateMgr->GetContext();
    auto view = ctx->window->getDefaultView().getSize();

    m_titleLabel = std::make_shared<Label>(
            "TFall",
            ctx->fonts->get(MW::Resources::Font::Main),
            static_cast<int32_t>(MW::FontSize::StateInfo)
    );
    auto bounds = m_titleLabel->GetLocalBounds();
    m_titleLabel->setOrigin(bounds.width / 2, bounds.height / 2);
    m_titleLabel->setPosition(view.x / 2, view.y / 2 - 50);

    m_instructionsLabel = std::make_shared<Label>(
            "Press Enter to Start",
            ctx->fonts->get(MW::Resources::Font::Main),
            static_cast<int32_t>(MW::FontSize::StateInfo)
    );
    bounds = m_instructionsLabel->GetLocalBounds();
    m_instructionsLabel->setOrigin(bounds.width / 2, bounds.height / 2);
    m_instructionsLabel->setPosition(view.x / 2, view.y / 2 + 50);

    auto instructionsLabelColor = m_instructionsLabel->GetFillColor();
    instructionsLabelColor.a = 0;
    m_instructionsLabel->SetFillColor(instructionsLabelColor);

    ctx->inputManager->AddCallback<MenuState>(MW::StateType::MainMenu, "start_game", &MenuState::onEnter, this);
}

void MenuState::OnDestroy()
{
    auto ctx = m_stateMgr->GetContext();
    ctx->inputManager->RemoveCallback(MW::StateType::MainMenu, "start_game");
}

void MenuState::Activate()
{

}

void MenuState::Deactivate()
{

}

void MenuState::Update(const sf::Time &l_time)
{
    m_alphaAccumulator = std::fmod(m_alphaAccumulator + l_time.asSeconds(), static_cast<float>((M_PI * 2)));
    auto instructionsLabelColor = m_instructionsLabel->GetFillColor();
    instructionsLabelColor.a = static_cast<sf::Uint8>(255 * std::fabs(std::sin(m_alphaAccumulator)));
    m_instructionsLabel->SetFillColor(instructionsLabelColor);
}

void MenuState::Draw()
{
    auto ctx = m_stateMgr->GetContext();
    ctx->window->draw(*m_titleLabel);
    ctx->window->draw(*m_instructionsLabel);
}

void MenuState::onEnter(MW::EventDetails* eventDetails)
{
    m_stateMgr->SwitchTo(MW::StateType::Game);
}
