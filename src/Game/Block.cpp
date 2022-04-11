//
// Created by Admin on 19.03.2022.
//

#include "Block.hpp"
#include <MW/Utility/Utility.h>

Block::Block(TetrisGridSettings& settings, float margin, sf::Texture& texture, sf::IntRect textureRect) :
//    gridContext(gridContext),
    posX(0),
    posY(0),
    inFullLine(false)
{
//    auto newSize = sf::Vector2f(gridContext.gridSettings.unitGridSize - 2*margin, gridContext.gridSettings.unitGridSize - 2*margin);
//    sprite.setTexture(texture);
//    sprite.setTextureRect(textureRect);
//    auto textureScaleRatio = vectorScaleRatio(newSize, sf::Vector2f(static_cast<float>(textureRect.width), static_cast<float>(textureRect.height)));
//    sprite.setScale(textureScaleRatio.x, textureScaleRatio.y);
//
//    auto origin = sf::Vector2f(-margin / textureScaleRatio.x, -margin / textureScaleRatio.y);
//    sprite.setOrigin(origin);
}

Block::~Block() {

}

bool Block::isMarkedForRemoval() const {
    return inFullLine;
}

void Block::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Block::updateCurrent(sf::Time dt, MW::CommandQueue &commands) {

}

void Block::move(sf::Vector2i diff) {
    setGridPosition(sf::Vector2i(posX + diff.x, posY + diff.y));
}

void Block::setGridPosition(sf::Vector2i pos) {
//    posX = pos.x;
//    posY = pos.y;
//
//    setPosition(sf::Vector2f(static_cast<float>(posX), static_cast<float>(posY))*gridContext.gridSettings.unitGridSize);
}

sf::Vector2i Block::getGridPosition() const {
    return {posX, posY};
}

