//
// Created by Admin on 16.03.2022.
//

#include "TextNode.h"
#include <Resources/FontConsts.h>
#include <cmath>

TextNode::TextNode(const FontHolder& fonts) :
        SceneNode(),
        text()
{
    text.setCharacterSize(static_cast<unsigned int>(Engine::FontSize::PlayerInfo));
    text.setFont(fonts.get(Engine::Resources::Font::Main));
}

void TextNode::setText(const std::string& str)
{
    text.setString(str);

    auto localBounds = text.getLocalBounds();
    setOrigin(floorf(localBounds.left + localBounds.width / 2), floorf(localBounds.top + localBounds.height / 2));
}

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(text, states);
}

void TextNode::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    // Ничего
}

