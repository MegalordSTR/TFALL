//
// Created by Admin on 21.03.2022.
//

#include "Player.hpp"
#include "Figure.hpp"

Player::Player() {

}

void Player::handleInputEvents(const sf::Event& event, MW::CommandQueue& queue) {
    switch (event.type) {
        case sf::Event::KeyPressed:
        {
            switch (event.key.code) {
                case sf::Keyboard::Up:
                {
                    auto action = MW::derrivedAction<Figure>(
                            [](Figure& node, sf::Time) {
                                if (node.isPlayerMovable()) {
                                    node.rotateRight();
                                }
                            }
                    );
                    queue.push(MW::Command(action, MW::CategoryType::TypeFigure));
                }
                    break;
                case sf::Keyboard::Left:
                {
                    auto action = MW::derrivedAction<Figure>(
                            [](Figure& node, sf::Time) {
                                if (node.isPlayerMovable()) {
                                    node.move(sf::Vector2i(-1, 0));
                                }
                            }
                    );
                    queue.push(MW::Command(action, MW::CategoryType::TypeFigure));
                }
                    break;
                case sf::Keyboard::Right:
                {
                    auto action = MW::derrivedAction<Figure>(
                            [](Figure& node, sf::Time) {
                                if (node.isPlayerMovable()) {
                                    node.move(sf::Vector2i(1, 0));
                                }
                            }
                    );
                    queue.push(MW::Command(action, MW::CategoryType::TypeFigure));
                }
                    break;
                default:
                    break;
            }
        }
        default: ;
    }
}
