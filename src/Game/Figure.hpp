//
// Created by Admin on 19.03.2022.
//

#ifndef TFALL_FIGURE_HPP
#define TFALL_FIGURE_HPP

#include <Engine/Node/SceneNode.hpp>

#include "Block.hpp"

#include <vector>
#include <memory>



class Figure : public Engine::SceneNode {
public:
    enum class RotateDirection
    {
        Left = 0,
        Right = 1
    };

    Figure(bool isStatic);

    virtual ~Figure();

    void attachBlock(const std::shared_ptr<Block>& ptr);
    std::shared_ptr<Block> detachBlock(const Block& node);

    void rotate(RotateDirection dir);

private:
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

    void updateCurrent(sf::Time dt, Engine::CommandQueue &commands) override;

    std::vector<int> getFullLinesNums();

    void moveDownLinesAbove(std::vector<int> lines);

private:
    bool isStatic;

    std::vector<std::weak_ptr<Block>> blocks;
};


#endif //TFALL_FIGURE_HPP
