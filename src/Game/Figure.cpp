//
// Created by Admin on 19.03.2022.
//

#include "Figure.hpp"

Figure::Figure(bool isStatic) :
    isStatic(isStatic)
{}

Figure::~Figure() {

}

void Figure::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {

}

void Figure::updateCurrent(sf::Time dt, Engine::CommandQueue &commands) {
    if (!isStatic)
    {
        for (auto& item : blocks)
        {
            if (auto block = item.lock())
            {
                block->move(sf::Vector2i(0, 1));
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

void Figure::rotate(Figure::RotateDirection dir) {

}

std::vector<int> Figure::getFullLinesNums() {
    return std::vector<int>();
}

void Figure::moveDownLinesAbove(std::vector<int> lines) {

}
