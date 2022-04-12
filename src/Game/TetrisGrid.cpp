//
// Created by Admin on 30.03.2022.
//

#include "TetrisGrid.hpp"
#include "GridSpriteNode.hpp"

#include <stdexcept>
#include <cassert>

TetrisGrid::TetrisGrid(TetrisGridSettings &settings, sf::Texture &blockTexture) :
        settings(settings),
        blockTexture(blockTexture)
{
    int size = settings.size.x * settings.size.y;
    blockGrid.reserve(size);
    for (int i = 0; i < settings.size.y; i++) {
        for (int j = 0; j < settings.size.x; j++) {
            blockGrid.emplace_back(std::shared_ptr<MW::SpriteNode>(nullptr), BlockType::None, j, i);
        }
    }
    spawnFigure(settings.size.x / 2, TetrisGrid::BlockType::PlayerFalling);
}

void TetrisGrid::spawnBlock(int x, int y, TetrisGrid::BlockType type, int texNum) {
    auto &block = getBlock(x, y);
    if (block.type != TetrisGrid::BlockType::None)
    {
        throw std::logic_error("can not spawn sprite on existing sprite");
    }

    auto sprite = std::make_shared<MW::SpriteNode>(
            MW::Vec2f(settings.unitGridSize, settings.unitGridSize),
            blockTexture,
            MW::RectI(30,30,30 * texNum,0)
    );
    attachChild(sprite);

    block.type = type;
    block.blockSprite = sprite;
    sprite->setPosition(block.x * settings.unitGridSize, block.y * settings.unitGridSize);
}

void TetrisGrid::spawnFigure(int x, TetrisGrid::BlockType type) {
    int texNum = rand() % 5;

    spawnBlock(x + 0, 0, type, texNum);
    spawnBlock(x + 0, 1, type, texNum);
    spawnBlock(x + 0, 2, type, texNum);
    spawnBlock(x + 1, 2, type, texNum);
}

void TetrisGrid::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {

}

bool TetrisGrid::hasToBeStatic(const Block &block)
{
    switch (block.type) {
        case TetrisGrid::BlockType::None:
            return false;
        case TetrisGrid::BlockType::Static:
            return true;
        default:
            break;
    }

    if (settings.size.y - 1 <= block.y)
    {
        return true;
    }

    auto &n = getBlock(block.x, block.y + 1);
    if (n.type == TetrisGrid::BlockType::Static)
    {
        return true;
    }

    return false;
}

void TetrisGrid::updateCurrent(sf::Time dt, MW::CommandQueue& commands) {
    bool playerBlockChangedType = updatePlayerFigure();

    for (auto &tgBlock : blockGrid)
    {
        if (tgBlock.type == TetrisGrid::BlockType::Static || tgBlock.type == TetrisGrid::BlockType::None)
        {
            continue;
        }

        if (hasToBeStatic(tgBlock))
        {
            tgBlock.type = TetrisGrid::BlockType::Static;
        }
        else
        {
            tgBlock.derivedMove.x = tgBlock.x;
            tgBlock.derivedMove.y = tgBlock.y + 1;
        }
    }

    for (auto &tgBlock : blockGrid)
    {
        bool needMove = tgBlock.NeedMove();
        ExecuteDerivedMoveBlock(tgBlock);
        if (needMove)
        {
            tgBlock.type = hasToBeStatic(tgBlock) ? BlockType::Static : tgBlock.type;
        }
    }


    for (int y = 0; y < settings.size.y; y++)
    {
        int staticBlocksAtLine = 0;
        for (int x = 0; x < settings.size.x; x++)
        {
            if (getBlock(x, y).type == TetrisGrid::BlockType::Static)
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

    if (playerBlockChangedType)
    {
//        int randX = rand() % settings.size.x;
//        if (blockGrid[0][randX] == TetrisGrid::BlockType::None)
//        {
//            spawnBlock(randX, 0, TetrisGrid::BlockType::PlayerFalling);
//        }
        spawnFigure(settings.size.x / 2, TetrisGrid::BlockType::PlayerFalling);
    }
}

TetrisGrid::BlockGrid TetrisGrid::makeGrid() const {
    BlockGrid grid;
    int size = settings.size.x * settings.size.y;
    grid.reserve(size);
    for (int i = 0; i < settings.size.y; i++) {
        for (int j = 0; j < settings.size.x; j++) {
            grid.emplace_back(std::shared_ptr<MW::SpriteNode>(nullptr), BlockType::None, i, j);
        }
    }
    return grid;
}

void TetrisGrid::shrinkLine(int y) {
    for (auto &tgBlock : blockGrid)
    {
        if (tgBlock.y == y)
        {
            clearBlock(tgBlock);
        }
        else if (tgBlock.y < y)
        {
            tgBlock.type = tgBlock.type != BlockType::None ? BlockType::Falling : tgBlock.type;
        }
    }
}

void TetrisGrid::MovePlayerFigure(int x) {
    vector<Block*> playerBlocks;
    for (auto &block : blockGrid)
    {
        if (block.IsPlayer())
        {
            playerBlocks.push_back(&block);
        }
    }

    for (auto blockP : playerBlocks)
    {
        Block &block = *blockP;
        int newX = block.x + x;
        // Выезд за сетку
        if (newX < 0 || newX >= settings.size.x)
        {
            return;
        }

        // Попадание в другую фигуру
        TetrisGrid::BlockType newXCellType = getBlock(newX, block.y).type;
        if (newXCellType != BlockType::None && !(static_cast<uint32_t>(newXCellType) & static_cast<uint32_t>(BlockType::Player)))
        {
            return;
        }
    }

    for (auto blockP : playerBlocks)
    {
        Block &block = *blockP;

        block.derivedMove.x = block.x + x;
        block.derivedMove.y = block.y;
    }

    for (auto blockP : playerBlocks)
    {
        Block &block = *blockP;

        ExecuteDerivedMoveBlock(block);
    }
}

void TetrisGrid::RotatePlayerFigure() {
//    auto playerBlocks = std::find_if(blocks.begin(), blocks.end(), [&](const auto& item){
//        return item->IsPlayer();
//    });
//
//    int figureLeft = (**playerBlocks).x;
//    int figureTop = (**playerBlocks).y;
//    // Расчет фигуры
//    for (auto it = playerBlocks; it != blocks.end(); it++)
//    {
//        Block& block = **it;
//        figureLeft = block.x < figureLeft ? block.x : figureLeft;
//        figureTop = block.y < figureTop ? block.y : figureTop;
//    }
//
//    // Проверка новых координат
//    for (auto it = playerBlocks; it != blocks.end(); it++)
//    {
//        Block& block = **it;
//        int newX = figureLeft + figureTop - block.y;
//        int newY = block.y + figureTop - figureLeft;
//
//        // Выезд за сетку
//        if (newX < 0 || newX >= settings.size.x)
//        {
//            return;
//        }
//
//        if (newY < 0 || newY >= settings.size.y)
//        {
//            return;
//        }
//
//        // Попадание в другую фигуру
//        TetrisGrid::BlockType newXCellType = blockGrid[newY][newX];
//        if (newXCellType != BlockType::None && !(static_cast<uint32_t>(newXCellType) & static_cast<uint32_t>(BlockType::Player)))
//        {
//            return;
//        }
//    }
//
//    // Перемещение по новым координатам
//    for (auto it = playerBlocks; it != blocks.end(); it++)
//    {
//        Block& block = **it;
//
//        int newX = figureLeft + figureTop - block.y;
//        int newY = block.y + figureTop - figureLeft;
//
//        block.MoveTo(blockGrid, newX, newY);
//        block.blockSprite->setPosition(block.x * settings.unitGridSize, block.y * settings.unitGridSize);
//    }

//    remakeBlockGrid();
}

bool TetrisGrid::updatePlayerFigure() {
    bool anyConvertToStatic = false;
    for (const auto &block : blockGrid)
    {
        if (block.IsPlayer())
        {
            anyConvertToStatic |= hasToBeStatic(block);
        }
    }

    if (anyConvertToStatic) {
        for (auto &block: blockGrid) {
            if (block.IsPlayer()) {
                block.type = TetrisGrid::BlockType::Static;
            }
        }
    }

    return anyConvertToStatic;
}

TetrisGrid::Block &TetrisGrid::getBlock(int x, int y) {
    assert(x < settings.size.x);
    assert(y < settings.size.y);

    return blockGrid.at(x + y * settings.size.x);
}

void TetrisGrid::clearBlock(TetrisGrid::Block &block) {
    detachChild(*block.blockSprite.lock());
    block.blockSprite.reset();
    block.type = BlockType::None;
    block.ResetMove();
}

TetrisGrid::Block &TetrisGrid::getBlock(const MW::Vec2i coord){
    return getBlock(coord.x, coord.y);
}

void TetrisGrid::ExecuteDerivedMoveBlock(TetrisGrid::Block &block) {
    if (!block.NeedMove())
        return;

    auto &newBlock = getBlock(block.derivedMove);
    ExecuteDerivedMoveBlock(newBlock);
    if (newBlock.type == BlockType::None)
    {
        newBlock.blockSprite = block.blockSprite;
        newBlock.blockSprite.lock()->setPosition(newBlock.x * settings.unitGridSize, newBlock.y * settings.unitGridSize);
        newBlock.type = block.type;

        block.blockSprite.reset();
        block.type = BlockType::None;
    }

    block.ResetMove();
}

