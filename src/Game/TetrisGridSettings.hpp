#pragma once

#include <MW/Core/Mwtype.hpp>
#include <cstdint>

struct TetrisGridSettings
{
    MW::Vec2i size;
    int32_t unitGridSize;

    TetrisGridSettings(const int xSize, const int ySize, const int unitGridSize = 10) :
            size(xSize, ySize),
            unitGridSize(unitGridSize)
    {}
};
