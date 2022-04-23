#pragma once

#include <MW/Node/SceneNode.hpp>
#include "TetrisGridSettings.hpp"

#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>

class GridSpriteNode : public MW::SceneNode {
public:
    GridSpriteNode(const TetrisGridSettings& settings, const sf::Color gridColor = sf::Color::Black, const float gridThickness = 2.f);
    ~GridSpriteNode() override;

private:
    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
    void updateCurrent(sf::Time dt, MW::CommandQueue &commands) override;

private:
    std::vector<std::unique_ptr<sf::RectangleShape>> lines;
};
