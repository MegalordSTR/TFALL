//
// Created by Admin on 01.04.2022.
//

#ifndef TFALL_SPRITENODE_HPP
#define TFALL_SPRITENODE_HPP

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


#endif //TFALL_SPRITENODE_HPP
