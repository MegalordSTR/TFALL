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

    struct Block {
        int x;
        int y;

        BlockType type;
        std::weak_ptr<MW::SpriteNode> blockSprite;

        MW::Vec2i derivedMove;

        Block(std::shared_ptr<MW::SpriteNode> blockSprite, BlockType type, int x, int y) :
            x(x), y(y), type(type), blockSprite(blockSprite), derivedMove(-1, -1) {}

        bool IsPlayer() const
        {
            return static_cast<uint32_t>(type) & static_cast<uint32_t>(BlockType::Player);
        }

        bool NeedMove() const
        {
            return derivedMove.x != -1;
        }

        void ResetMove()
        {
            derivedMove.x = -1;
            derivedMove.y = -1;
        }
    };

    typedef vector<Block> BlockGrid;
    TetrisGrid(TetrisGridSettings &settings, sf::Texture &blockTexture);
    ~TetrisGrid() override = default;

    void MovePlayerFigure(int x);
    void RotatePlayerFigure();

private:
    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;

    void updateCurrent(sf::Time dt, MW::CommandQueue &commands) override;

    BlockGrid makeGrid() const;
    void spawnBlock(int x, int y, TetrisGrid::BlockType type = BlockType::Falling, int texNum = 0);
    void spawnFigure(int x, TetrisGrid::BlockType type);

    Block &getBlock(int x, int y);
    Block &getBlock(const MW::Vec2i coord);
    void clearBlock(Block &block);
    void ExecuteDerivedMoveBlock(Block &block);

    void shrinkLine(int y);
    bool updatePlayerFigure();
    bool hasToBeStatic(const Block &block);
private:
    TetrisGridSettings settings;
    BlockGrid blockGrid;

    sf::Texture& blockTexture;
};


#endif //TFALL_TETRISGRID_HPP
