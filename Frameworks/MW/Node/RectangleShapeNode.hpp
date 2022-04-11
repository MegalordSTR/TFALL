//
// Created by Admin on 31.03.2022.
//

#ifndef TFALL_RECTANGLESHAPENODE_HPP
#define TFALL_RECTANGLESHAPENODE_HPP

#include "SceneNode.hpp"
#include <MW/Core/Mwtype.hpp>

namespace MW
{
    class RectangleShapeNode : public SceneNode {
    public:
        explicit RectangleShapeNode(Vec2f size);
        ~RectangleShapeNode() override;

        void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
        void setFillColor(const sf::Color& color);
        void setOutlineColor(const sf::Color& color);
        void setOutlineThickness(float thickness);
        Vec2f getSize() const;

    private:
        sf::RectangleShape rectangleShape;
    };
}

#endif //TFALL_RECTANGLESHAPENODE_HPP
