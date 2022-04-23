#include "GridSpriteNode.hpp"

GridSpriteNode::GridSpriteNode(const TetrisGridSettings& settings, const sf::Color gridColor, const float gridThickness) :
    lines()
{
    int linesVert = settings.size.x - 1;
    int linesHor = settings.size.y - 1;
    float unitGridSizeF = static_cast<float>(settings.unitGridSize);

    lines.reserve(linesVert + linesHor);

    for (int i = 0; i < linesVert; i++)
    {
        auto line = std::make_unique<sf::RectangleShape>(sf::Vector2f(
                gridThickness,
                unitGridSizeF * static_cast<float>(settings.size.y)
                ));

        line->setPosition(unitGridSizeF * static_cast<float>(i+1), 0);
        lines.push_back(std::move(line));
    }

    for (int i = 0; i < linesHor; i++)
    {
        auto line = std::make_unique<sf::RectangleShape>(sf::Vector2f(
                unitGridSizeF * static_cast<float>(settings.size.x),
                gridThickness
                ));
        line->setPosition(0, unitGridSizeF * static_cast<float>(i+1));
        lines.push_back(std::move(line));
    }

    for (auto& line : lines) {
        line->setFillColor(gridColor);
    }
}

GridSpriteNode::~GridSpriteNode() {

}

void GridSpriteNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto& line : lines) {
        target.draw(*line, states);
    }
}

void GridSpriteNode::updateCurrent(sf::Time dt, MW::CommandQueue &commands) {

}
