//
// Created by Admin on 20.04.2022.
//

#ifndef TFALL_LABEL_HPP
#define TFALL_LABEL_HPP

#include "SceneNode.hpp"

namespace MW
{
    class Label : public SceneNode {
    public:
        Label(const std::string &text, const sf::Font &font, int32_t size);

        void SetText(const std::string &l_text);
        void SetFont(const sf::Font &font);
        void SetCharacterSize(int32_t size);

        std::string GetText() const;
        const sf::Font &GetFont() const;
        int32_t GetCharacterSize() const;

    private:
        void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;

    private:
        sf::Text text;
    };
}

#endif //TFALL_LABEL_HPP
