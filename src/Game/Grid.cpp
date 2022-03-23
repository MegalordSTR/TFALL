//
// Created by Admin on 19.03.2022.
//

#include "Grid.hpp"

Grid::Grid(float xSize, float ySize, sf::Color gridColor, float unitGridSize, float gridThickness) :
    lines()
{
    int xLines = static_cast<int>((xSize - unitGridSize) / unitGridSize);
    int yLines = static_cast<int>((ySize - unitGridSize) / unitGridSize);

    lines.reserve(xLines + yLines);

    for (int i = 0; i < xLines; i++)
    {
        auto line = std::make_unique<sf::RectangleShape>(sf::Vector2f(gridThickness, unitGridSize * static_cast<float>(yLines+1)));
        line->setPosition(unitGridSize * static_cast<float>(i+1), 0);
        lines.push_back(std::move(line));
    }

    for (int i = 0; i < yLines; i++)
    {
        auto line = std::make_unique<sf::RectangleShape>(sf::Vector2f(unitGridSize * static_cast<float>(xLines+1), gridThickness));
        line->setPosition(0, unitGridSize * static_cast<float>(i+1));
        lines.push_back(std::move(line));
    }

    for (auto& line : lines) {
        line->setFillColor(gridColor);
    }
}

Grid::~Grid() {

}

void Grid::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto& line : lines) {
        target.draw(*line, states);
    }
}

void Grid::updateCurrent(sf::Time dt, MW::CommandQueue &commands) {

}