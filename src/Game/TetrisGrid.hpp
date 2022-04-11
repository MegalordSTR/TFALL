//
// Created by Admin on 30.03.2022.
//

#ifndef TFALL_TETRISGRID_HPP
#define TFALL_TETRISGRID_HPP

#include "TetrisGridSettings.hpp"
#include "GridSpriteNode.hpp"

#include <MW/Node/SceneNode.hpp>
#include <MW/Node/SpriteNode.hpp>
#include <MW/Core/Mwtype.hpp>

#include <memory>
#include <vector>

using std::vector;

class TetrisGrid : public MW::SceneNode {
public:
    enum class BlockType : uint32_t
    {
        None = 0,
        Falling = 1 << 0,
        Static = 1 << 1,
        Player = 1 << 2,
        PlayerFalling = Falling | Player
    };

    typedef vector<BlockType> BlockRow;
    typedef vector<BlockRow> BlockGrid;

    struct Block {
        int x;
        int y;
        BlockType type;

        std::shared_ptr<MW::SpriteNode> blockSprite;

        Block(std::shared_ptr<MW::SpriteNode> &blockSprite, BlockType type, int x, int y) :
            x(x), y(y), type(type), blockSprite(blockSprite) {}

        void MoveTo(BlockGrid &grid, int newX, int newY)
        {
            grid[y][x] = BlockType::None;

            x = newX;
            y = newY;
            grid[y][x] = type;
        }

        void ChangeType(BlockGrid &grid, BlockType newType)
        {
            type = newType;
            grid[y][x] = type;
        }

        bool IsPlayer()
        {
            return static_cast<uint32_t>(type) & static_cast<uint32_t>(BlockType::Player);
        }
    };


    TetrisGrid(TetrisGridSettings &settings, sf::Texture &blockTexture);
    ~TetrisGrid() override = default;

private:
    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;

    void updateCurrent(sf::Time dt, MW::CommandQueue &commands) override;

    BlockGrid makeGrid() const;
    void spawnBlock(int x, int y, TetrisGrid::BlockType type = BlockType::Falling);

    void shrinkLine(int y);

    void movePlayerFigure(int x);

private:
    TetrisGridSettings settings;

    BlockGrid blockGrid;
    vector<std::shared_ptr<Block>> blocks;

    sf::Texture& blockTexture;
};


#endif //TFALL_TETRISGRID_HPP
