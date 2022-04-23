#include "RectangleShapeNode.hpp"


MW::RectangleShapeNode::RectangleShapeNode(Vec2f size) :
        rectangleShape(sf::Vector2f(size.x, size.y))
{
}

MW::RectangleShapeNode::~RectangleShapeNode() = default;

void MW::RectangleShapeNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(rectangleShape, states);
}

void MW::RectangleShapeNode::setFillColor(const sf::Color& color) {
    rectangleShape.setFillColor(color);
}

void MW::RectangleShapeNode::setOutlineColor(const sf::Color& color) {
    rectangleShape.setOutlineColor(color);
}

void MW::RectangleShapeNode::setOutlineThickness(float thickness) {
    rectangleShape.setOutlineThickness(thickness);
}

MW::Vec2f MW::RectangleShapeNode::getSize() const {
    auto size = rectangleShape.getSize();
    return {size.x, size.y};
}
