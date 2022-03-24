//
// Created by Admin on 19.03.2022.
//

#ifndef TFALL_GRID_HPP
#define TFALL_GRID_HPP

#include <MW/Node/SceneNode.hpp>

#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>

class Grid : public MW::SceneNode {
public:
    struct GridSettings
    {
        int xLines;
        int yLines;
        float unitGridSize;

        GridSettings(const float xSize, const float ySize, const float unitGridSize = 10.f) :
            xLines(static_cast<int>((xSize - unitGridSize) / unitGridSize)),
            yLines(static_cast<int>((ySize - unitGridSize) / unitGridSize)),
            unitGridSize(unitGridSize)
        {}
    };

    Grid(const GridSettings& gridSettings, const sf::Color gridColor = sf::Color::Black, const float gridThickness = 2.f);
    ~Grid() override;

    const GridSettings& getGridSettings();

private:
    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;

    void updateCurrent(sf::Time dt, MW::CommandQueue &commands) override;

private:
    std::vector<std::unique_ptr<sf::RectangleShape>> lines;
    GridSettings settings;
};


#endif //TFALL_GRID_HPP
