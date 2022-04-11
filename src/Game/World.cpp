//
// Created by Admin on 18.03.2022.
//

#include "World.hpp"
#include "TetrisGridSettings.hpp"



#include <MW/Node/RectangleShapeNode.hpp>
#include <MW/Node/SpriteNode.hpp>
#include <MW/Utility/Utility.h>

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <functional>

const sf::Vector2f mapSize(400, 560);

World::World(sf::RenderWindow& window, MW::SoundPlayer& soundPlayer, MW::TextureHolder& textureHolder) :
        textureHolder(textureHolder),
        commandQueue(),
        sceneManager(),
        soundPlayer(soundPlayer),
        window(window),
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
    tetrisGrid = std::make_shared<TetrisGrid>(tgs, textureHolder.get(MW::Resources::Texture::Block));
    frontLayer.attachChild(tetrisGrid);
    tetrisGrid->setPosition(mapPanel->getPosition());

    // Музыка
    // soundPlayer.play(MW::Resources::TypeSoundEffect::Background); // TODO включить музыку и вынести в отд контейнер
}


World::~World() {

}

// Обновление объектов на один игровой шаг
void World::update(sf::Time dt) {
    auto& frontLayer = sceneManager.getLayer(MW::Layer::Front);
    frontLayer.update(dt, commandQueue);
//    auto fallingFigureLock = fallingFigure.lock();
//    if (fallingFigureLock->getAllBlocks().empty())
//    {
//
//        spawnFigure(nextFigureColorNum);
//        nextFigureColorNum = (nextFigureColorNum + 1) % figureColorsNum;
//    }
//
//    if (isFigureLanded())
//    {
//        transferNonStaticFigure();
//        shrinkFullLines();
//    }
//
//    auto& frontLayer = sceneManager.getLayer(MW::Layer::Front);
//
//    while (!commandQueue.isEmpty())
//    {
//        frontLayer.onCommand(commandQueue.pop(), dt);
//    }
//
//    frontLayer.update(dt, commandQueue);
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

