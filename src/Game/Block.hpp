//
// Created by Admin on 19.03.2022.
//

#ifndef TFALL_BLOCK_HPP
#define TFALL_BLOCK_HPP

#include <MW/Node/SceneNode.hpp>

class Block : public MW::SceneNode {
public:
    Block(sf::Vector2u size, int margin, sf::Texture& texture, sf::IntRect textureRect);

    virtual ~Block();

    bool isMarkedForRemoval() const override;

    void move(sf::Vector2i diff);
    sf::Vector2i getGridPosition();

private:
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

    void updateCurrent(sf::Time dt, MW::CommandQueue &commands) override;

private:
    int posX;
    int posY;
    sf::Vector2u size;

    bool inFullLine;

    sf::Sprite sprite;
};


#endif //TFALL_BLOCK_HPP
