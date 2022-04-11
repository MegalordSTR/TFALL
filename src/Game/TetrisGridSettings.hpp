//
// Created by Admin on 30.03.2022.
//

#ifndef TFALL_TETRISGRIDSETTINGS_HPP
#define TFALL_TETRISGRIDSETTINGS_HPP

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

#endif //TFALL_TETRISGRIDSETTINGS_HPP
