//
// Created by Admin on 19.03.2022.
//

#include "Figure.hpp"

Figure::Figure(bool isStatic) :
    isStatic(isStatic)
{
    setNodeCategory(MW::CategoryType::TypeFigure);
}

Figure::~Figure() {

}

void Figure::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {

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
}

void Figure::attachBlock(const std::shared_ptr<Block>& ptr) {
    attachChild(ptr);
    blocks.push_back(std::weak_ptr(ptr));
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
    return result;
}

void Figure::rotateRight() {
    int figureSize = calculateFigureSize();
    for (auto& item : blocks)
    {
        if (auto block = item.lock())
        {
            auto pos = block->getGridPosition();
            block->move(sf::Vector2i(figureSize - pos.y, pos.x));
        }
    }
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

int Figure::calculateFigureSize() {
    int minX, minY;
    int maxX, maxY;
    minX = minY = maxX = maxY = 0;

    for (auto& item : blocks)
    {
        if (auto block = item.lock())
        {
            auto pos = block->getGridPosition();
            if (pos.x < minX)
                minX = pos.x;
            if (pos.x > maxX)
                maxX = pos.x;
            if (pos.x < minY)
                minY = pos.y;
            if (pos.x > maxY)
                maxY = pos.y;
        }
    }

    return std::max(maxX - minX, maxY - minY);
}

#pragma clang diagnostic pop
