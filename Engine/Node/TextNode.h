//
// Created by Admin on 16.03.2022.
//

#ifndef TEST_TEXTNODE_H
#define TEST_TEXTNODE_H

#include "SceneNode.h"
#include <Resources/ResourceHolder.h>
#include <Resources/ResourceIdentifiers.h>

#include <SFML/Graphics.hpp>

#include <string>

namespace Engine
{
    class TextNode : public SceneNode
    {
    public:
        explicit TextNode(const FontHolder& fonts);

        void setText(const std::string& str);
    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
        virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

    private:
        sf::Text text;
    };
}



#endif //TEST_TEXTNODE_H
