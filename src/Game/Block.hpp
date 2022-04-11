//
// Created by Admin on 19.03.2022.
//

#ifndef TFALL_BLOCK_HPP
#define TFALL_BLOCK_HPP

#include <MW/Node/SceneNode.hpp>

#include "TetrisGridSettings.hpp"

class Block : public MW::SceneNode {
public:
    Block(TetrisGridSettings& settings, float margin, sf::Texture& texture, sf::IntRect textureRect);

    ~Block() override;

    bool isMarkedForRemoval() const override;

    void move(sf::Vector2i diff);
    void setGridPosition(sf::Vector2i pos);

    sf::Vector2i getGridPosition() const;

private:
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

    void updateCurrent(sf::Time dt, MW::CommandQueue &commands) override;

private:
    int posX;
    int posY;

    bool inFullLine;

    sf::Sprite sprite;
};


#endif //TFALL_BLOCK_HPP
