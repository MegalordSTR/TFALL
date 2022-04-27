#include "App.hpp"
#include <States/GameState.hpp>

App::App(int windowWidth, int windowHeight, float targetFPS) :
        window(sf::VideoMode(windowWidth, windowHeight), "App", sf::Style::Close),
        targetFPS(targetFPS),
        timePerFrame(sf::seconds(1 / targetFPS)),
        inputManager(),
        fontHolder(),
        textureHolder(),
        soundPlayer(),
        stateManager(nullptr)
{
    ctx = std::make_shared<MW::SharedContext>();
    ctx->window = &window;
    ctx->inputManager = &inputManager;
    ctx->fonts = &fontHolder;
    ctx->textures = &textureHolder;
    ctx->soundPlayer = &soundPlayer;

    stateManager = std::make_shared<MW::StateManager>(ctx.get());

    window.setKeyRepeatEnabled(false);
    textureHolder.load(MW::Resources::Texture::Block, "blocks.png");
    fontHolder.load(MW::Resources::Font::Main, "Sansation.ttf");

    inputManager.AddCallback<App>(MW::StateType::Game, "window_close", &App::closeWindow, this);

    stateManager->RegisterState<GameState>(MW::StateType::Game);
    stateManager->SwitchTo(MW::StateType::Game);
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
        inputManager.HandleEvent(event);
    }

    inputManager.Update();
}

void App::update(sf::Time dt) {
    stateManager->Update(dt);
}

void App::render() {
    window.clear(sf::Color::White);
    stateManager->Draw();
    window.display();
}

void App::closeWindow(MW::EventDetails* details) {
    window.close();
}
