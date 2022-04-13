//
// Created by Admin on 30.03.2022.
//

#include "TetrisGrid.hpp"
#include "GridSpriteNode.hpp"

#include <MW/Utility/Utility.h>

#include <cassert>
#include <stack>


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
    HasPlayerSpace = spawnFigure(settings.size.x / 2, TetrisGrid::BlockType::PlayerFalling);
}

void TetrisGrid::spawnBlock(int x, int y, TetrisGrid::BlockType type, int texNum) {
    auto &block = getBlock(x, y);
    if (block.type != TetrisGrid::BlockType::None)
    {
        throw std::logic_error("can not spawn block on existing block");
    }

    auto sprite = std::make_shared<MW::SpriteNode>(
            MW::Vec2f(static_cast<float>(settings.unitGridSize), static_cast<float>(settings.unitGridSize)),
            blockTexture,
            MW::RectI(30,30,30 * texNum,0)
    );
    attachChild(sprite);

    block.type = type;
    block.blockSprite = sprite;
    sprite->setPosition(static_cast<float>(block.x * settings.unitGridSize), static_cast<float>(block.y * settings.unitGridSize));
}

bool TetrisGrid::spawnFigure(int x, TetrisGrid::BlockType type) {
    vector<MW::Vec2i> coords;

    switch (randIntN(5)) {
        case 0: // квадрат
            coords.emplace_back(MW::Vec2i(x + 0, 0));
            coords.emplace_back(MW::Vec2i(x + 1, 0));
            coords.emplace_back(MW::Vec2i(x + 0, 1));
            coords.emplace_back(MW::Vec2i(x + 1, 1));
            break;
        case 1: // Z
            coords.emplace_back(MW::Vec2i(x + -1, 0));
            coords.emplace_back(MW::Vec2i(x + 0, 0));
            coords.emplace_back(MW::Vec2i(x + 0, 1));
            coords.emplace_back(MW::Vec2i(x + 1, 1));
            break;
        case 2: // L
            coords.emplace_back(MW::Vec2i(x + 0, 0));
            coords.emplace_back(MW::Vec2i(x + 0, 1));
            coords.emplace_back(MW::Vec2i(x + 0, 2));
            coords.emplace_back(MW::Vec2i(x + 1, 2));
            break;
        case 3: // T
            coords.emplace_back(MW::Vec2i(x + -1, 0));
            coords.emplace_back(MW::Vec2i(x + 0, 0));
            coords.emplace_back(MW::Vec2i(x + 1, 0));
            coords.emplace_back(MW::Vec2i(x + 0, 1));
            break;
        case 4: // I
            coords.emplace_back(MW::Vec2i(x + 0, 0));
            coords.emplace_back(MW::Vec2i(x + 0, 1));
            coords.emplace_back(MW::Vec2i(x + 0, 2));
            coords.emplace_back(MW::Vec2i(x + 0, 3));
            break;
    }


    for (auto& coord : coords)
    {
        auto &block = getBlock(coord.x, coord.y);
        if (block.type != TetrisGrid::BlockType::None)
        {
            return false;
        }
    }

    int texNum = randIntN(5);
    for (auto& coord : coords)
    {
        spawnBlock(coord.x, coord.y, BlockType::PlayerFalling, texNum);
    }

    return true;
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
    if (!HasPlayerSpace)
        return;

    // Сдвиг блоков на убранные линии
    for (auto &tgBlock : blockGrid)
    {
        ExecuteDerivedMoveBlock(tgBlock);
    }

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
        HasPlayerSpace = spawnFigure(settings.size.x / 2, TetrisGrid::BlockType::PlayerFalling);
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
        else if (tgBlock.y < y && tgBlock.type != BlockType::None && !tgBlock.IsPlayer())
        {
            tgBlock.derivedMove.x = tgBlock.x;
            tgBlock.derivedMove.y = tgBlock.derivedMove.y == -1 ? tgBlock.y + 1 : tgBlock.derivedMove.y + 1;
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
    if (playerBlocks.empty())
    {
        return;
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

bool TetrisGrid::isValidPlayerPosition(int x, int y)
{
    // Выезд за сетку
    if (x < 0 || x >= settings.size.x)
    {
        return false;
    }

    if (y < 0 || y >= settings.size.y)
    {
        return false;
    }

    // Попадание в другую фигуру
    TetrisGrid::Block newCell = getBlock(x, y);
    if (newCell.type != BlockType::None && !newCell.IsPlayer())
    {
        return false;
    }

    return true;
}

void TetrisGrid::RotatePlayerFigure() {
    vector<Block*> playerBlocks;
    for (auto &block : blockGrid)
    {
        if (block.IsPlayer())
        {
            playerBlocks.push_back(&block);
        }
    }
    if (playerBlocks.empty())
        return;

    // Расчет фигуры
    int figureLeft = (*playerBlocks[0]).x;
    int figureTop = (*playerBlocks[0]).y;
    for (auto blockP : playerBlocks)
    {
        Block &block = *blockP;

        figureLeft = block.x < figureLeft ? block.x : figureLeft;
        figureTop = block.y < figureTop ? block.y : figureTop;
    }

    int newFigureLeft = settings.size.x;
    int newFigureTop = settings.size.y;
    // Проверка новых координат
    for (auto blockP : playerBlocks)
    {
        Block &block = *blockP;

        int newX = figureLeft + figureTop - block.y;
        int newY = block.x + figureTop - figureLeft;

        if (!isValidPlayerPosition(newX, newY))
            return;

        newFigureLeft = newX < newFigureLeft ? newX : newFigureLeft;
        newFigureTop = newY < newFigureTop ? newY : newFigureTop;
    }

    int shiftX = figureLeft - newFigureLeft;
    int shiftY = figureTop - newFigureTop;
    // Проверка новых координат (со сдвигом)
    for (auto blockP : playerBlocks)
    {
        Block &block = *blockP;

        int newX = figureLeft + figureTop - block.y;
        int newY = block.x + figureTop - figureLeft;

        int newShiftedX = shiftX + newX;
        int newShiftedY = shiftY + newY;

        if (!isValidPlayerPosition(newShiftedX, newShiftedY))
            return;
    }


    // Перемещение по новым координатам
    for (auto blockP : playerBlocks)
    {
        Block &block = *blockP;

        int newX = figureLeft + figureTop - block.y;
        int newY = block.x + figureTop - figureLeft;

        int newShiftedX = shiftX + newX;
        int newShiftedY = shiftY + newY;

        block.derivedMove.x = newShiftedX;
        block.derivedMove.y = newShiftedY;
    }

    for (auto blockP : playerBlocks)
    {
        Block &block = *blockP;

        ExecuteDerivedMoveBlock(block);
    }
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

    std::stack<Block*> blocks;
    blocks.push(&block);

    auto nextBlock = &getBlock(block.derivedMove);
    while (nextBlock->NeedMove() && *nextBlock != block)
    {
        blocks.push(nextBlock);
        nextBlock = &getBlock(nextBlock->derivedMove);
    }

    while (!blocks.empty())
    {
        auto &currentBlock = *blocks.top();
        blocks.pop();

        auto& newBlock = getBlock(currentBlock.derivedMove);
        if (newBlock.type == BlockType::None)
        {
            newBlock.blockSprite = currentBlock.blockSprite;
            newBlock.blockSprite.lock()->setPosition(static_cast<float>(newBlock.x * settings.unitGridSize), static_cast<float>(newBlock.y * settings.unitGridSize));
            newBlock.type = currentBlock.type;

            currentBlock.blockSprite.reset();
            currentBlock.type = BlockType::None;
        }

        currentBlock.ResetMove();
    }
}

vector<TetrisGrid::Block*> TetrisGrid::getBlocksOfType(TetrisGrid::BlockType type) {
    vector<Block*> blocks;
    for (auto &block : blockGrid)
    {
        if (block.type == type)
        {
            blocks.push_back(&block);
        }
    }

    return blocks;
}

