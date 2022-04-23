#pragma once

#include "SceneNode.hpp"
#include <MW/Core/Mwtype.hpp>

namespace MW
{
    class SpriteNode : public SceneNode{
    public:
        explicit SpriteNode(Vec2f size, sf::Texture& texture, MW::RectI textureRect);
        ~SpriteNode() override;

        Vec2f getSize() const;

    private:
        void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

        void updateCurrent(sf::Time dt, CommandQueue& commands) override;

    private:
        sf::Sprite sprite;
    };

}
