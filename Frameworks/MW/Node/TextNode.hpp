//
// Created by Admin on 16.03.2022.
//

#ifndef TEST_TEXTNODE_H
#define TEST_TEXTNODE_H

#include "SceneNode.hpp"
#include <MW/Resources/ResourceHolder.hpp>
#include <MW/Resources/ResourceIdentifiers.hpp>

#include <SFML/Graphics.hpp>

#include <string>

namespace MW
{
    class TextNode : public SceneNode
    {
    public:
        explicit TextNode(const FontHolder& fonts);

        ~TextNode() override;

        void setText(const std::string& str);
    private:
        void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
        void updateCurrent(sf::Time dt, CommandQueue& commands) override;

    private:
        sf::Text text;
    };
}



#endif //TEST_TEXTNODE_H
