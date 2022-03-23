//
// Created by Admin on 19.03.2022.
//

#ifndef TFALL_FIGURE_HPP
#define TFALL_FIGURE_HPP

#include <MW/Node/SceneNode.hpp>

#include "Block.hpp"
#include "Grid.hpp"

#include <vector>
#include <memory>



class Figure : public MW::SceneNode {
public:
    Figure(const Grid::GridSettings& gridSettings, bool isStatic);

    virtual ~Figure();

    void attachBlock(const std::shared_ptr<Block>& ptr);
    std::shared_ptr<Block> detachBlock(const Block& node);

    void rotateRight();
    void move(sf::Vector2i diff);
    bool isPlayerMovable() const;

    void switchDrawRect();

private:
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    void updateCurrent(sf::Time dt, MW::CommandQueue &commands) override;

    std::vector<int> getFullLinesNums();
    void moveDownLinesAbove(std::vector<int> lines);
    bool checkValidOfBlocksPositions();

    sf::IntRect calculateFigureRect();

private:
    Grid::GridSettings gridSettings;

    bool isStatic;
    std::vector<std::weak_ptr<Block>> blocks;

    sf::RectangleShape figureRectShape;
    sf::IntRect gridFigureRect;
    bool drawRect;
};


#endif //TFALL_FIGURE_HPP
