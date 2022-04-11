//
// Created by Admin on 01.04.2022.
//

#include "SpriteNode.hpp"

MW::SpriteNode::SpriteNode(MW::Vec2f size, sf::Texture& texture, MW::RectI textureRect) :
    sprite(texture, sf::IntRect(textureRect.left, textureRect.top, textureRect.width, textureRect.height))
{
    auto textureScaleRatio = size / MW::Vec2f (static_cast<float>(textureRect.width), static_cast<float>(textureRect.height));
    sprite.setScale(textureScaleRatio.x, textureScaleRatio.y);

//    auto origin = sf::Vector2f(1-textureScaleRatio.x, 1-1/textureScaleRatio.y);
//    sprite.setOrigin(origin);
}

MW::SpriteNode::~SpriteNode() = default;

MW::Vec2f MW::SpriteNode::getSize() const {
    auto bounds = sprite.getLocalBounds();
    return {bounds.width, bounds.height};
}

void MW::SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void MW::SpriteNode::updateCurrent(sf::Time dt, MW::CommandQueue& commands) {

}

