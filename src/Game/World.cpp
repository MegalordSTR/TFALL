//
// Created by Admin on 18.03.2022.
//

#include "World.hpp"
#include "Block.hpp"
#include "Figure.hpp"
//#include "Block.hpp"

#include <Engine/Utility/Utility.h>

#include <memory>

const sf::Vector2f mapSize(400, 480);

World::World(sf::RenderWindow& window, Engine::SoundPlayer& soundPlayer, Engine::TextureHolder& textureHolder) :
    commandQueue(),
    sceneManager(),
    backgroundBig(sf::Vector2f(mapSize.x + 100, mapSize.y + 100)),
    backgroundMap(mapSize),
    soundPlayer(soundPlayer),
    window(window),
    worldView(window.getDefaultView())
{
    sceneManager.addLayer(Engine::Layer::Background);
    auto& backgroundLayer = sceneManager.getLayer(Engine::Layer::Background);
    sceneManager.addLayer(Engine::Layer::Front);
    auto& frontLayer = sceneManager.getLayer(Engine::Layer::Front);

    float unitGridSize = 40;
    float gridThickness = 1;
    gridMargin = 1;

    auto gridColor = sf::Color(0,0,0,25);
    auto gridNode = std::make_shared<Grid>(
            mapSize.x,
            mapSize.y,
            gridColor,
            unitGridSize,
            gridThickness
            );

    grid = gridNode;
    backgroundLayer.attachChild(gridNode);

    backgroundBig.setFillColor(sf::Color(200,200,200,255));

    sf::Vector2f backgroundBigCenter(backgroundBig.getPosition() + divideVector(backgroundBig.getSize(), 2.f));
    sf::Vector2f backgroundMapCenter(backgroundMap.getPosition() + divideVector(backgroundMap.getSize(), 2.f));
    backgroundMap.move(backgroundBigCenter - backgroundMapCenter);
    backgroundMap.setOutlineThickness(3);
    backgroundMap.setOutlineColor(sf::Color::Black);

    if (auto lockedGrid = grid.lock())
    {
        lockedGrid->setPosition(backgroundMap.getPosition());
    }

    soundPlayer.play(Engine::Resources::SoundEffect::Background); // TODO включить музыку и вынести в отд контейнер

    sf::Texture t;
    sf::Sprite s;
    auto testBlock = std::make_shared<Block>(
            sf::Vector2u(static_cast<unsigned int>(unitGridSize), static_cast<unsigned int>(unitGridSize)),
            gridMargin,
            textureHolder.get(Engine::Resources::Texture::Block),
            sf::IntRect(0,0,30, 30)
            );



    auto figure = std::make_shared<Figure>(false);
    figure->setPosition(backgroundMap.getPosition());
    figure->attachBlock(testBlock);
    frontLayer.attachChild(figure);
}

World::~World() {

}

void World::update(sf::Time dt) {
    auto& frontLayer = sceneManager.getLayer(Engine::Layer::Front);
    frontLayer.update(dt, commandQueue);
}

void World::draw() {
    window.draw(backgroundBig);
    window.draw(backgroundMap);

    auto& frontLayer = sceneManager.getLayer(Engine::Layer::Front);
    window.draw(frontLayer);
    auto& backgroundLayer = sceneManager.getLayer(Engine::Layer::Background);
    window.draw(backgroundLayer);
}
