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
    Grid(float xSize, float ySize, sf::Color gridColor = sf::Color::Black, float unitGridSize = 10.f, float gridThickness = 2.f);
    ~Grid() override;

private:
    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;

    void updateCurrent(sf::Time dt, MW::CommandQueue &commands) override;

private:
    std::vector<std::unique_ptr<sf::RectangleShape>> lines;
};


#endif //TFALL_GRID_HPP
