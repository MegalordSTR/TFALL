//
// Created by Admin on 18.03.2022.
//

#include "World.hpp"
#include "TetrisGridSettings.hpp"

#include <MW/Node/RectangleShapeNode.hpp>
#include <MW/Node/SpriteNode.hpp>
#include <MW/Utility/Utility.h>
#include <MW/Resources/FontConsts.hpp>

#include <memory>

const sf::Vector2f mapSize(400, 560);

World::World(sf::RenderWindow &window, MW::SoundPlayer &soundPlayer, MW::TextureHolder &textureHolder, MW::FontHolder &fontsHolder, MW::InputManager &inputManager) :
        window(window),
        soundPlayer(soundPlayer),
        textureHolder(textureHolder),
        inputManager(inputManager),
        commandQueue(),
        sceneManager(),
        worldView(window.getDefaultView()),
        nextFigureColorNum(0),
        figureColorsNum(5),
        tetrisGrid()
{
    // Слои
    sceneManager.addLayer(MW::Layer::Background);
    auto& backgroundLayer = sceneManager.getLayer(MW::Layer::Background);
    sceneManager.addLayer(MW::Layer::Front);
    auto& frontLayer = sceneManager.getLayer(MW::Layer::Front);

    const int ugs = 40;
    TetrisGridSettings tgs(static_cast<int>(mapSize.x)/ugs, static_cast<int>(mapSize.y)/ugs, ugs);

    // Карта и информационная панель
    auto viewSize = worldView.getSize();
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


    tetrisGrid = std::make_shared<TetrisGrid>(tgs, textureHolder.get(MW::Resources::Texture::Block), label);
    frontLayer.attachChild(tetrisGrid);
    frontLayer.attachChild(label);
    tetrisGrid->setPosition(mapPanel->getPosition());
    label->setPosition(mapPanel->getPosition() + sf::Vector2f(mapPanel->getSize().x / 2, -50));

    inputManager.AddCallback<World>("move_left", &World::moveFigureLeft, this);
    inputManager.AddCallback<World>("move_right", &World::moveFigureRight, this);
    inputManager.AddCallback<World>("rotate", &World::rotateFigure, this);

    // Музыка
    soundPlayer.play(MW::Resources::SoundEffect::Background); // TODO включить музыку и вынести в отд контейнер
}


World::~World() {

}

// Обновление объектов на один игровой шаг
void World::update(sf::Time dt) {
    auto& frontLayer = sceneManager.getLayer(MW::Layer::Front);
    frontLayer.update(dt, commandQueue);
}

/// Отрисовывает все объекты в мире игры
void World::draw() {
    auto& backgroundLayer = sceneManager.getLayer(MW::Layer::Background);
    window.draw(backgroundLayer);

    auto& frontLayer = sceneManager.getLayer(MW::Layer::Front);
    window.draw(frontLayer);
}

MW::CommandQueue& World::getCommandQueue() {
    return commandQueue;
}

void World::moveFigureLeft(MW::EventDetails* details) {
    tetrisGrid->MovePlayerFigure(-1);
}

void World::moveFigureRight(MW::EventDetails* details) {
    tetrisGrid->MovePlayerFigure(1);
}

void World::rotateFigure(MW::EventDetails* details) {
    tetrisGrid->RotatePlayerFigure();
}

bool World::CheckSpace() {
    return tetrisGrid->HasPlayerSpace;
}

int32_t World::GetScore() {
    return tetrisGrid->GetShrinkedLinesCount();
}

