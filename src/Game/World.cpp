//
// Created by Admin on 18.03.2022.
//

#include "World.hpp"
#include "Block.hpp"
#include "Figure.hpp"

#include <MW/Utility/Utility.h>

#include <memory>

const sf::Vector2f mapSize(400, 480);

World::World(sf::RenderWindow& window, MW::SoundPlayer& soundPlayer, MW::TextureHolder& textureHolder) :
        commandQueue(),
        sceneManager(),
        infoPanel(),
        mapPanel(mapSize),
        soundPlayer(soundPlayer),
        window(window),
        worldView(window.getDefaultView())
{
    // Слои
    sceneManager.addLayer(MW::Layer::Background);
    auto& backgroundLayer = sceneManager.getLayer(MW::Layer::Background);
    sceneManager.addLayer(MW::Layer::Front);
    auto& frontLayer = sceneManager.getLayer(MW::Layer::Front);

    // Карта и информационная панель
    infoPanel.setSize(worldView.getSize());
    infoPanel.setFillColor(sf::Color(200, 200, 200, 255));

    sf::Vector2f infoPanelLeftCenter(0, infoPanel.getSize().y / 2);
    sf::Vector2f mapPanelLeftCenter(mapPanel.getPosition() + sf::Vector2f(0, mapPanel.getSize().y / 2));
    mapPanel.setOrigin(mapPanelLeftCenter);
    mapPanel.move(sf::Vector2f(100, 0) + infoPanelLeftCenter - infoPanel.getPosition());
    mapPanel.setOutlineThickness(3);
    mapPanel.setOutlineColor(sf::Color::Black);

    // Сетка
    float gridThickness = 1;
    gridMargin = 1.f;
    Grid::GridSettings gridSettings(mapSize.x,mapSize.y,40);

    auto gridColor = sf::Color(0,0,0,25);
    auto gridNode = std::make_shared<Grid>(
            gridSettings,
            gridColor,
            gridThickness
    );

    grid = gridNode;
    backgroundLayer.attachChild(gridNode);

    if (auto lockedGrid = grid.lock())
    {
        lockedGrid->setOrigin(mapPanel.getOrigin());
        lockedGrid->setPosition(mapPanel.getPosition());
    }

    // Фигуры
    sf::Texture t;
    sf::Sprite s;
    auto testBlock = std::make_shared<Block>(
            gridSettings,
            gridMargin,
            textureHolder.get(MW::Resources::Texture::Block),
            sf::IntRect(0,0,30, 30)
            );
    auto testBlock2 = std::make_shared<Block>(
            gridSettings,
            gridMargin,
            textureHolder.get(MW::Resources::Texture::Block),
            sf::IntRect(0,0,30, 30)
            );
    auto testBlock3 = std::make_shared<Block>(
            gridSettings,
            gridMargin,
            textureHolder.get(MW::Resources::Texture::Block),
            sf::IntRect(0,0,30, 30)
            );
    auto testBlock4 = std::make_shared<Block>(
            gridSettings,
            gridMargin,
            textureHolder.get(MW::Resources::Texture::Block),
            sf::IntRect(0,0,30, 30)
            );



    auto figure = std::make_shared<Figure>(gridSettings, false);
    figure->setOrigin(mapPanel.getOrigin());
    figure->setPosition(mapPanel.getPosition());

    figure->attachBlock(testBlock);
    figure->attachBlock(testBlock2);
    figure->attachBlock(testBlock3);
    figure->attachBlock(testBlock4);

    testBlock->move(sf::Vector2i(0,0));
    testBlock2->move(sf::Vector2i(1,0));
    testBlock3->move(sf::Vector2i(2,0));
    testBlock4->move(sf::Vector2i(2,1));

    frontLayer.attachChild(figure);

    figure->switchDrawRect();
    // Музыка
    // soundPlayer.play(MW::Resources::TypeSoundEffect::Background); // TODO включить музыку и вынести в отд контейнер
}


World::~World() {

}

// Обновление объектов на один игровой шаг
void World::update(sf::Time dt) {
    auto& frontLayer = sceneManager.getLayer(MW::Layer::Front);

    while (!commandQueue.isEmpty())
    {
        frontLayer.onCommand(commandQueue.pop(), dt);
    }

    frontLayer.update(dt, commandQueue);
}

/// Отрисовывает все объекты в мире игры
void World::draw() {
    window.draw(infoPanel);
    window.draw(mapPanel);

    auto& frontLayer = sceneManager.getLayer(MW::Layer::Front);
    window.draw(frontLayer);
    auto& backgroundLayer = sceneManager.getLayer(MW::Layer::Background);
    window.draw(backgroundLayer);
}

MW::CommandQueue& World::getCommandQueue() {
    return commandQueue;
}
