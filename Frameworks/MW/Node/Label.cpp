//
// Created by Admin on 20.04.2022.
//

#include "Label.hpp"



MW::Label::Label(const std::string &text, const sf::Font &font, int32_t size) :
        text(text, font, size)
{}

void MW::Label::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(text, states);
}

void MW::Label::SetText(const std::string &l_text) {
    text.setString(l_text);
}

void MW::Label::SetFont(const sf::Font &font) {
    text.setFont(font);
}

void MW::Label::SetCharacterSize(int32_t size) {
    text.setCharacterSize(size);
}

std::string MW::Label::GetText() const {
    return text.getString();
}

const sf::Font &MW::Label::GetFont() const {
    return *text.getFont();
}

int32_t MW::Label::GetCharacterSize() const {
    return static_cast<int32_t>(text.getCharacterSize());
}
