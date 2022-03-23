//
// Created by Admin on 19.03.2022.
//

#ifndef TFALL_FIGURE_HPP
#define TFALL_FIGURE_HPP

#include <MW/Node/SceneNode.hpp>

#include "Block.hpp"

#include <vector>
#include <memory>



class Figure : public MW::SceneNode {
public:
    Figure(bool isStatic);

    virtual ~Figure();

    void attachBlock(const std::shared_ptr<Block>& ptr);
    std::shared_ptr<Block> detachBlock(const Block& node);

    void rotateRight();
    void move(sf::Vector2i diff);
    bool isPlayerMovable() const;

private:
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    void updateCurrent(sf::Time dt, MW::CommandQueue &commands) override;

    std::vector<int> getFullLinesNums();
    void moveDownLinesAbove(std::vector<int> lines);
    bool checkValidOfBlocksPositions();

    int calculateFigureSize();

private:
    bool isStatic;

private:
    std::vector<std::weak_ptr<Block>> blocks;
};


#endif //TFALL_FIGURE_HPP
