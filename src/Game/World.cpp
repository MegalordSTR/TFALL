#include "World.hpp"
#include "TetrisGridSettings.hpp"

#include <MW/Node/RectangleShapeNode.hpp>
#include <MW/Node/SpriteNode.hpp>
#include "MW/Utility/Utility.hpp"
#include <MW/Resources/FontConsts.hpp>
#include "MW/Core/StateManager.hpp"

#include <memory>

const sf::Vector2f mapSize(400, 560);

World::World(sf::RenderWindow &window, MW::SoundPlayer &soundPlayer, MW::TextureHolder &textureHolder, MW::FontHolder &fontsHolder, MW::InputManager &inputManager) :
        m_window(window),
        m_soundPlayer(soundPlayer),
        m_textureHolder(textureHolder),
        m_inputManager(inputManager),
        m_commandQueue(),
        m_sceneManager(),
        m_worldView(window.getDefaultView()),
        m_tetrisGrid()
{
    // Слои
    m_sceneManager.addLayer(MW::Layer::Background);
    auto& backgroundLayer = m_sceneManager.getLayer(MW::Layer::Background);
    m_sceneManager.addLayer(MW::Layer::Front);
    auto& frontLayer = m_sceneManager.getLayer(MW::Layer::Front);

    const int ugs = 40;
    TetrisGridSettings tgs(static_cast<int>(mapSize.x)/ugs, static_cast<int>(mapSize.y)/ugs, ugs);

    // Карта и информационная панель
    auto viewSize = m_worldView.getSize();
    auto infoPanel = std::make_shared<MW::RectangleShapeNode>(MW::Vec2f(viewSize.x, viewSize.y));
    infoPanel->setFillColor(sf::Color(200, 200, 200, 255));
    backgroundLayer.attachChild(infoPanel);

    auto mapPanel = std::make_shared<MW::RectangleShapeNode>(MW::Vec2f(mapSize.x, mapSize.y));
    mapPanel->setOutlineThickness(3);
    mapPanel->setOutlineColor(sf::Color::Black);
    backgroundLayer.attachChild(mapPanel);

    // Спрайт сетки
    auto gridSprite = std::make_shared<GridSpriteNode>(tgs, sf::Color(0,0,0,25));
    mapPanel->attachChild(gridSprite);

    auto infoPanelSize = infoPanel->getSize();
    auto mapPanelSize = mapPanel->getSize();
    MW::Vec2f centerDiff(200, ((infoPanelSize.y - mapPanelSize.y) / 2));

    mapPanel->move(centerDiff.x, centerDiff.y);

    // Фигуры
    auto label = std::make_shared<MW::Label>("", fontsHolder.get(MW::Resources::Font::Main),static_cast<int32_t>(MW::FontSize::StateInfo));


    m_tetrisGrid = std::make_shared<TetrisGrid>(tgs, m_textureHolder.get(MW::Resources::Texture::Block), label);
    frontLayer.attachChild(m_tetrisGrid);
    frontLayer.attachChild(label);
    m_tetrisGrid->setPosition(mapPanel->getPosition());
    label->setPosition(mapPanel->getPosition() + sf::Vector2f(mapPanel->getSize().x / 2, -50));

    m_inputManager.AddCallback<World>(MW::StateType::Game, "move_left", &World::moveFigureLeft, this);
    m_inputManager.AddCallback<World>(MW::StateType::Game, "move_right", &World::moveFigureRight, this);
    m_inputManager.AddCallback<World>(MW::StateType::Game, "rotate", &World::rotateFigure, this);

    // Музыка
    m_soundPlayer.play(MW::Resources::SoundEffect::Background); // TODO включить музыку и вынести в отд контейнер
}


World::~World() {
    m_inputManager.RemoveCallback(MW::StateType::Game, "move_left");
    m_inputManager.RemoveCallback(MW::StateType::Game, "move_right");
    m_inputManager.RemoveCallback(MW::StateType::Game, "rotate");
}

// Обновление объектов на один игровой шаг
void World::update(sf::Time dt) {
    auto& frontLayer = m_sceneManager.getLayer(MW::Layer::Front);
    frontLayer.update(dt, m_commandQueue);
}

/// Отрисовывает все объекты в мире игры
void World::draw() {
    auto& backgroundLayer = m_sceneManager.getLayer(MW::Layer::Background);
    m_window.draw(backgroundLayer);

    auto& frontLayer = m_sceneManager.getLayer(MW::Layer::Front);
    m_window.draw(frontLayer);
}

MW::CommandQueue& World::getCommandQueue() {
    return m_commandQueue;
}

void World::moveFigureLeft(MW::EventDetails* details) {
    m_tetrisGrid->MovePlayerFigure(-1);
}

void World::moveFigureRight(MW::EventDetails* details) {
    m_tetrisGrid->MovePlayerFigure(1);
}

void World::rotateFigure(MW::EventDetails* details) {
    m_tetrisGrid->RotatePlayerFigure();
}

bool World::CheckSpace() {
    return m_tetrisGrid->HasPlayerSpace;
}

int32_t World::GetScore() {
    return m_tetrisGrid->GetShrinkedLinesCount();
}

void World::ToggleDebug() {
    m_debugEnabled = !m_debugEnabled;
}

