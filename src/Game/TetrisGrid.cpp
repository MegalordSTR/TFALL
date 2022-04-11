//
// Created by Admin on 30.03.2022.
//

#include "TetrisGrid.hpp"
#include "GridSpriteNode.hpp"

#include <stdexcept>

TetrisGrid::TetrisGrid(TetrisGridSettings &settings, sf::Texture &blockTexture) :
        settings(settings),
        blockTexture(blockTexture)
{
    blockGrid = makeGrid();
    spawnBlock(0, 0, TetrisGrid::BlockType::PlayerFalling);
}

void TetrisGrid::spawnBlock(int x, int y, TetrisGrid::BlockType type) {
    if (blockGrid[y][x] != TetrisGrid::BlockType::None)
    {
        throw std::logic_error("can not spawn block on existing block");
    }

    int texNum = rand() % 5;
    auto block = std::make_shared<MW::SpriteNode>(
            MW::Vec2f(settings.unitGridSize, settings.unitGridSize),
            blockTexture,
            MW::RectI(30,30,30 * texNum,0)
    );
    attachChild(block);

    auto tgBlock = std::make_shared<Block>(block, type, x, y);
    tgBlock->blockSprite->setPosition(tgBlock->x * settings.unitGridSize, tgBlock->y * settings.unitGridSize);
    blockGrid[y][x] = tgBlock->type;
    blocks.push_back(tgBlock);
}

void TetrisGrid::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {

}

void TetrisGrid::updateCurrent(sf::Time dt, MW::CommandQueue& commands) {
    bool needToSpawn = false;

    for (auto &tgBlock : blocks)
    {
        if (tgBlock->type == TetrisGrid::BlockType::Static)
        {
            continue;
        }

        bool isPlayer = tgBlock->IsPlayer();

        if (blockGrid[tgBlock->y + 1][tgBlock->x] == TetrisGrid::BlockType::Static)
        {
            tgBlock->ChangeType(blockGrid, TetrisGrid::BlockType::Static);
        }
        else
        {
            tgBlock->MoveTo(blockGrid, tgBlock->x, tgBlock->y + 1);
            tgBlock->blockSprite->setPosition(tgBlock->x * settings.unitGridSize, tgBlock->y * settings.unitGridSize);
        }

        if (settings.size.y - 1 == tgBlock->y)
        {
            tgBlock->ChangeType(blockGrid, TetrisGrid::BlockType::Static);
        }

        needToSpawn = isPlayer && tgBlock->type == TetrisGrid::BlockType::Static;
    }


    for (int y = 0; y < blockGrid.size(); y++)
    {
        int staticBlocksAtLine = 0;
        for (int x = 0; x < blockGrid[y].size(); x++)
        {
            if (blockGrid[y][x] == TetrisGrid::BlockType::Static)
            {
                staticBlocksAtLine++;
            }
            else
            {
                break;
            }
        }

        if (staticBlocksAtLine == settings.size.x)
        {
            shrinkLine(y);
        }
    }

    if (needToSpawn)
    {
        int randX = rand() % settings.size.x;
        if (blockGrid[0][randX] == TetrisGrid::BlockType::None)
        {
            spawnBlock(randX, 0, TetrisGrid::BlockType::PlayerFalling);
        }
    }
}

TetrisGrid::BlockGrid TetrisGrid::makeGrid() const {
    BlockGrid grid;
    grid.reserve(settings.size.y);
    for (int i = 0; i < settings.size.y; i++) {
        grid.emplace_back(BlockRow());
        for (int j = 0; j < settings.size.x; j++) {
            grid.at(i).emplace_back(TetrisGrid::BlockType::None);
        }
    }
    return grid;
}

void TetrisGrid::shrinkLine(int y) {
    for (auto &tgBlock : blocks)
    {
        if (tgBlock->y == y)
        {
            tgBlock->ChangeType(blockGrid, BlockType::None);
            detachChild(*tgBlock->blockSprite);
        }
        else if (tgBlock->y < y)
        {
            tgBlock->ChangeType(blockGrid, BlockType::Falling);
        }
    }

    blocks.erase(std::remove_if(blocks.begin(), blocks.end(), [&](const auto& item){
        return item->type == BlockType::None;
    }), blocks.end());
}

void TetrisGrid::movePlayerFigure(int x) {
    auto playerBlocks = std::find_if(blocks.begin(), blocks.end(), [&](const auto& item){
        return item->IsPlayer();
    });

    for (auto it = playerBlocks; it != blocks.end(); it++)
    {
        Block& block = **it;
        int newX = block.x + x;
        // Выезд за сетку
        if (newX < 0 || newX >= blockGrid.size())
        {
            return;
        }

        // Попадание в другую фигуру
        TetrisGrid::BlockType newXCellType = blockGrid[block.y][newX];
        if (newXCellType != BlockType::None || !(static_cast<uint32_t>(newXCellType) & static_cast<uint32_t>(BlockType::Player)))
        {
            return;
        }
    }

    for (auto it = playerBlocks; it != blocks.end(); it++)
    {
        Block& block = **it;
        block.MoveTo(blockGrid, block.x + x, block.y);
    }
}
