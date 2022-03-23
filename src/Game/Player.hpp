//
// Created by Admin on 21.03.2022.
//

#ifndef TFALL_PLAYER_HPP
#define TFALL_PLAYER_HPP

#include <MW/Command/CommandQueue.hpp>
#include <MW/Command/Command.hpp>

#include <SFML/System.hpp>

#include <functional>
#include <memory>

class Player {
public:
    Player();

    void handleInputEvents(const sf::Event &event, MW::CommandQueue& queue);
};


#endif //TFALL_PLAYER_HPP
