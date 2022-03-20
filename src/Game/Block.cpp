//
// Created by Admin on 19.03.2022.
//

#include "Block.hpp"
#include <Engine/Utility/Utility.h>

Block::Block(sf::Vector2u size, int margin, sf::Texture& texture, sf::IntRect textureRect) :
    posX(0),
    posY(0),
    size(size),
    inFullLine(false)
{


    auto newSize = sf::Vector2u(size.x - 2*margin, size.y - 2*margin);
    sprite.setTexture(texture);
    sprite.setTextureRect(textureRect);
    auto textureScaleRatio = vectorScaleRatio(newSize, sf::Vector2u(textureRect.width, textureRect.height));
    sprite.setScale(static_cast<float>(textureScaleRatio.x), static_cast<float>(textureScaleRatio.y));

    auto origin = sf::Vector2f(static_cast<float>(-margin) / textureScaleRatio.x, static_cast<float>(-margin) / textureScaleRatio.y);
    sprite.setOrigin(origin);
}

Block::~Block() {

}

bool Block::isMarkedForRemoval() const {
    return inFullLine;
}

void Block::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Block::updateCurrent(sf::Time dt, Engine::CommandQueue &commands) {

}

void Block::move(sf::Vector2i diff) {
    posX += diff.x;
    posY += diff.y;

    setPosition(sf::Vector2f(static_cast<float>(posX*size.x), static_cast<float>(posY*size.x)));
}
