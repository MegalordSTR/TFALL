#pragma once

#include "SceneNode.hpp"
#include <MW/Core/Mwtype.hpp>
#include <SFML/Graphics.hpp>

namespace MW
{
    class Label : public SceneNode {
    public:
        Label(const std::string &text, const sf::Font &font, int32_t size);

        void SetText(const std::string &l_text);
        void SetFont(const sf::Font &font);
        void SetCharacterSize(int32_t size);
        void SetFillColor(const sf::Color color);

        std::string GetText() const;
        const sf::Font &GetFont() const;
        int32_t GetCharacterSize() const;
        sf::Color GetFillColor() const;

        MW::RectF GetLocalBounds() const;

    private:
        void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;

    private:
        sf::Text m_text;
    };
}
