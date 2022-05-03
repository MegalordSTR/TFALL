#include "Label.hpp"

MW::Label::Label(const std::string &text, const sf::Font &font, int32_t size) :
        m_text(text, font, size)
{
    m_text.setFillColor(sf::Color::Black);
}

void MW::Label::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_text, states);
}

void MW::Label::SetText(const std::string &l_text) {
    m_text.setString(l_text);
}

void MW::Label::SetFont(const sf::Font &font) {
    m_text.setFont(font);
}

void MW::Label::SetCharacterSize(int32_t size) {
    m_text.setCharacterSize(size);
}

std::string MW::Label::GetText() const {
    return m_text.getString();
}

const sf::Font &MW::Label::GetFont() const {
    return *m_text.getFont();
}

int32_t MW::Label::GetCharacterSize() const {
    return static_cast<int32_t>(m_text.getCharacterSize());
}

MW::RectF MW::Label::GetLocalBounds() const {
    auto sfLocalBounds = m_text.getLocalBounds();
    return {sfLocalBounds.width, sfLocalBounds.height, sfLocalBounds.left, sfLocalBounds.top};
}

void MW::Label::SetFillColor(const sf::Color color)
{
    m_text.setFillColor(color);
}

sf::Color MW::Label::GetFillColor() const
{
    return m_text.getFillColor();
}
