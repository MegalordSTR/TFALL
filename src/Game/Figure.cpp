//
// Created by Admin on 19.03.2022.
//

#include "Figure.hpp"

Figure::Figure(const Grid::GridSettings& gridSettings, bool isStatic) :
        gridSettings(gridSettings),
        isStatic(isStatic),
        drawRect(false),
        figureRectShape(),
        gridFigureRect()
{
    setNodeCategory(MW::CategoryType::TypeFigure);
    figureRectShape.setFillColor(sf::Color::Transparent);
    figureRectShape.setOutlineColor(sf::Color::Red);
    figureRectShape.setOutlineThickness(1.f);
}

Figure::~Figure() {

}

void Figure::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    if (drawRect)
        target.draw(figureRectShape, states);
}

void Figure::updateCurrent(sf::Time dt, MW::CommandQueue &commands) {
    if (!isStatic)
    {
        for (auto& item : blocks)
        {
            if (auto block = item.lock())
            {
                block->move(sf::Vector2i(0, 1));
                if (block->getGridPosition().y > 10)
                    move(sf::Vector2i(0, -10));
            }
        }
    }

    calculateFigureRect();
}

void Figure::attachBlock(const std::shared_ptr<Block>& ptr) {
    attachChild(ptr);
    blocks.push_back(std::weak_ptr(ptr));

    calculateFigureRect();
}

std::shared_ptr<Block> Figure::detachBlock(const Block& node) {
    auto found = std::find_if(
            blocks.begin(),
            blocks.end(),
            [&](const std::weak_ptr<SceneNode>& child)
            {
                if (auto locked = child.lock())
                {
                    return locked.get() == &node;
                }
                return false;
            }
    );

    assert(found != blocks.end());

    std::shared_ptr<Block> result = found->lock();
    blocks.erase(found);

    calculateFigureRect();
    return result;
}

void Figure::rotateRight() {
    for (auto& item : blocks)
    {
        if (auto block = item.lock())
        {
            auto pos = block->getGridPosition();
            block->setGridPosition(sf::Vector2i(
                    gridFigureRect.left + gridFigureRect.top - pos.y + 1, // NOTE: +1 только для того, чтобы фигура меньше съезжала
                    pos.x + gridFigureRect.top - gridFigureRect.left
                    ));
        }
    }

    calculateFigureRect();
}

std::vector<int> Figure::getFullLinesNums() {
    return std::vector<int>();
}

void Figure::moveDownLinesAbove(std::vector<int> lines) {

}

bool Figure::isPlayerMovable() const {
    return !isStatic;
}

void Figure::move(sf::Vector2i diff) {
    for (auto& item : blocks)
    {
        if (auto block = item.lock())
        {
            block->move(diff);
        }
    }

    if (!checkValidOfBlocksPositions())
    {
        for (auto& item : blocks)
        {
            if (auto block = item.lock())
            {
                block->move(-diff);
            }
        }
    }
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-use-anyofallof"
bool Figure::checkValidOfBlocksPositions()
{
    for (auto& item : blocks)
    {
        if (auto block = item.lock())
        {
            auto pos = block->getGridPosition();
            if (pos.x < 0 || pos.x > 10)
                return false;
        }
        else
        {
            return false;
        }
    }
    return true;
    // TODO добавить границы для блоков
}

void Figure::switchDrawRect() {
    drawRect = !drawRect;
}

sf::IntRect Figure::calculateFigureRect() {
    int minX, minY, maxX, maxY;
    minX = minY = maxX = maxY = 0;

    if (!blocks.empty())
    {
        if (auto block = blocks.front().lock())
        {
            auto pos = block->getGridPosition();
            minX = maxX = pos.x;
            minY = maxY = pos.y;
        }

        for (auto& item : blocks)
        {
            if (auto block = item.lock())
            {
                auto pos = block->getGridPosition();
                if (pos.x < minX)
                    minX = pos.x;
                if (pos.x > maxX)
                    maxX = pos.x;
                if (pos.y < minY)
                    minY = pos.y;
                if (pos.y > maxY)
                    maxY = pos.y;
            }
        }
    }

    int sideLength = std::max(maxX-minX, maxY-minY)+1;
    gridFigureRect = {
            minX,
            minY,
            sideLength,
            sideLength
    };

    figureRectShape.setSize(sf::Vector2f(static_cast<float>(gridFigureRect.width), static_cast<float>(gridFigureRect.height))*gridSettings.unitGridSize);
    figureRectShape.setPosition(sf::Vector2f(static_cast<float>(gridFigureRect.left), static_cast<float>(gridFigureRect.top))*gridSettings.unitGridSize);

    return gridFigureRect;
}

#pragma clang diagnostic pop
