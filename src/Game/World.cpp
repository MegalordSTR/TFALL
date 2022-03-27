//
// Created by Admin on 18.03.2022.
//

#include "World.hpp"



#include <MW/Utility/Utility.h>

#include <memory>
#include <unordered_map>
#include <unordered_set>

const sf::Vector2f mapSize(400, 560);

World::World(sf::RenderWindow& window, MW::SoundPlayer& soundPlayer, MW::TextureHolder& textureHolder) :
        textureHolder(textureHolder),
        commandQueue(),
        sceneManager(),
        infoPanel(),
        mapPanel(mapSize),
        soundPlayer(soundPlayer),
        window(window),
        worldView(window.getDefaultView()),
        nextFigureColorNum(0),
        figureColorsNum(5)
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

    // Статичная фигура
    auto staticFigureShared = std::make_shared<Figure>(gridSettings, true);
    staticFigure = staticFigureShared;

    staticFigureShared->setOrigin(mapPanel.getOrigin());
    staticFigureShared->setPosition(mapPanel.getPosition());

    frontLayer.attachChild(staticFigureShared);

    // Падающая фигура
    auto fallingFigureShared = std::make_shared<Figure>(gridSettings, false);
    fallingFigure = fallingFigureShared;

    fallingFigureShared->setOrigin(mapPanel.getOrigin());
    fallingFigureShared->setPosition(mapPanel.getPosition());

    frontLayer.attachChild(fallingFigureShared);

    fallingFigureShared->switchDrawRect();
    staticFigureShared->switchDrawRect();

    // Музыка
    // soundPlayer.play(MW::Resources::TypeSoundEffect::Background); // TODO включить музыку и вынести в отд контейнер
}


World::~World() {

}

// Обновление объектов на один игровой шаг
void World::update(sf::Time dt) {
    auto fallingFigureLock = fallingFigure.lock();
    if (fallingFigureLock->getAllBlocks().empty())
    {

        spawnFigure(nextFigureColorNum);
        nextFigureColorNum = (nextFigureColorNum + 1) % figureColorsNum;
    }

    if (isFigureLanded())
    {
        transferNonStaticFigure();
        shrinkFullLines();
    }

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

bool World::isFigureLanded() {
    // Проверка касания нижнего края
    auto gridSettings = grid.lock()->getGridSettings();
    auto fallingFigureLock = fallingFigure.lock();
    auto staticFigureLock = staticFigure.lock();

    std::vector<sf::Vector2i> fallingFigurePotentialBlocks = fallingFigureLock->getBlocksGridPositions();
    std::vector<sf::Vector2i> staticFigurePotentialBlocks = staticFigureLock->getBlocksGridPositions();

    for (auto& blockPos : fallingFigurePotentialBlocks) {
        if (blockPos.y == gridSettings.yLines)
            return true;
    }

    // Проверка касания фигуры снизу
    std::unordered_map<int, int> fallingFigureBottomBlocksPositions;

    for (auto& blockPos : fallingFigurePotentialBlocks) {
        auto found = fallingFigureBottomBlocksPositions.find(blockPos.x);
        if (found == fallingFigureBottomBlocksPositions.end())
        {
            fallingFigureBottomBlocksPositions.insert(std::make_pair(blockPos.x, blockPos.y));
        }
        else if (found->second < blockPos.y)
        {
            fallingFigureBottomBlocksPositions.insert_or_assign(blockPos.x, blockPos.y);
        }
    }

    for (auto& blockPos : staticFigurePotentialBlocks) {
        auto found = fallingFigureBottomBlocksPositions.find(blockPos.x);
        if (found != fallingFigureBottomBlocksPositions.end())
        {
            if (blockPos.y == found->second + 1)
            {
                return true;
            }
        }
    }

    return false;
}

void World::transferNonStaticFigure() {
    auto staticFigureLock = staticFigure.lock();
    auto fallingFigureLock = fallingFigure.lock();

    auto blocksToTransfer = fallingFigureLock->getAllBlocks();

    for (auto& blockWeak : blocksToTransfer) {
        if (auto blockLock = blockWeak.lock())
        {
            fallingFigureLock->detachBlock(*blockLock);
            staticFigureLock->attachBlock(blockLock);
        }
    }

}

void World::shrinkFullLines() {
    auto gridSettings = grid.lock()->getGridSettings();
    auto staticFigureLock = staticFigure.lock();

    auto blocks = staticFigureLock->getAllBlocks();

    std::unordered_map<int, int> blocksByLine;
    std::unordered_set<int> fullLines;

    for (auto& blockWeak : blocks) {
        if (auto blockLock = blockWeak.lock()) {
            auto pos = blockLock->getGridPosition();
            auto found = blocksByLine.find(pos.y);

            if (found == blocksByLine.end()) {
                blocksByLine.insert(std::make_pair(pos.y, 1));
            } else {
                if (found->second == gridSettings.xLines)
                    fullLines.insert(pos.y);

                blocksByLine.insert_or_assign(pos.y, found->second + 1);
            }
        }
    }

    std::vector<std::shared_ptr<Block>> blocksToDelete;

    for (auto& blockWeak : blocks) {
        if (auto blockLock = blockWeak.lock()) {
            auto pos = blockLock->getGridPosition();
            auto found = fullLines.count(pos.y);

            if (found == 1) {
                blocksToDelete.push_back(blockLock);
            }
        }
    }

    for (auto &item : blocksToDelete)
    {
        staticFigureLock->detachBlock(*item);
    }

    for (const auto &item : fullLines)
    {
        staticFigureLock->moveDownLinesAbove(item);
    }
}

void World::spawnFigure(int figureColor) {
    auto fallingFigureLock = fallingFigure.lock();
    auto gridSettings = grid.lock()->getGridSettings();

    auto testBlock = std::make_shared<Block>(
            gridSettings,
            gridMargin,
            textureHolder.get(MW::Resources::Texture::Block),
            sf::IntRect(30*(figureColor), 0, 30,30)
    );
    auto testBlock2 = std::make_shared<Block>(
            gridSettings,
            gridMargin,
            textureHolder.get(MW::Resources::Texture::Block),
            sf::IntRect(30*(figureColor),0,30, 30)
    );
    auto testBlock3 = std::make_shared<Block>(
            gridSettings,
            gridMargin,
            textureHolder.get(MW::Resources::Texture::Block),
            sf::IntRect(30*(figureColor),0,30, 30)
    );
    auto testBlock4 = std::make_shared<Block>(
            gridSettings,
            gridMargin,
            textureHolder.get(MW::Resources::Texture::Block),
            sf::IntRect(30*(figureColor),0,30, 30)
    );

    fallingFigureLock->attachBlock(testBlock);
    fallingFigureLock->attachBlock(testBlock2);
    fallingFigureLock->attachBlock(testBlock3);
    fallingFigureLock->attachBlock(testBlock4);

    testBlock->move(sf::Vector2i(0,0));
    testBlock2->move(sf::Vector2i(1,0));
    testBlock3->move(sf::Vector2i(2,0));
    testBlock4->move(sf::Vector2i(2,1));
}

