#pragma once

#include "GridSpriteNode.hpp"
#include "TetrisGrid.hpp"

#include <MW/Command/CommandQueue.hpp>
#include <MW/Node/SceneManager.hpp>
#include <MW/Node/SoundNode.hpp>
#include <MW/Node/Label.hpp>
#include "MW/Core/InputManager.hpp"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <memory>
#include <utility>

using MW::Label;

class World {
public:
    World(sf::RenderWindow &window, MW::SoundPlayer &soundPlayer, MW::TextureHolder &textureHolder, MW::FontHolder &fontsHolder, MW::InputManager &inputManager);

    ~World();

    void update(sf::Time dt);
    void draw();

    bool CheckSpace();
    int32_t GetScore();

    MW::CommandQueue& getCommandQueue();

    void SetDebugInfo();
    void ToggleDebug();

private:
    void moveFigureLeft(MW::EventDetails* details);
    void moveFigureRight(MW::EventDetails* details);
    void rotateFigure(MW::EventDetails* details);

private:
    sf::RenderWindow& m_window;
    MW::SoundPlayer& m_soundPlayer;
    MW::TextureHolder& m_textureHolder;
    MW::InputManager& m_inputManager;

    MW::CommandQueue m_commandQueue;
    MW::SceneManager m_sceneManager;

    sf::View m_worldView;

    std::shared_ptr<TetrisGrid> m_tetrisGrid;

    bool m_debugEnabled;
    std::shared_ptr<Label> m_debugLabel;
};
