//
// Created by Admin on 19.03.2022.
//

#include "Grid.hpp"

Grid::Grid(const GridSettings& gridSettings, const sf::Color gridColor, const float gridThickness) :
    lines(),
    settings(gridSettings)
{
    lines.reserve(gridSettings.xLines + gridSettings.yLines);

    for (int i = 0; i < gridSettings.xLines; i++)
    {
        auto line = std::make_unique<sf::RectangleShape>(sf::Vector2f(gridThickness, gridSettings.unitGridSize * static_cast<float>(gridSettings.yLines+1)));
        line->setPosition(gridSettings.unitGridSize * static_cast<float>(i+1), 0);
        lines.push_back(std::move(line));
    }

    for (int i = 0; i < gridSettings.yLines; i++)
    {
        auto line = std::make_unique<sf::RectangleShape>(sf::Vector2f(gridSettings.unitGridSize * static_cast<float>(gridSettings.xLines+1), gridThickness));
        line->setPosition(0, gridSettings.unitGridSize * static_cast<float>(i+1));
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

const Grid::GridSettings& Grid::getGridSettings() {
    return settings;
}
