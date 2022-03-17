//
// Created by Admin on 17.03.2022.
//

#ifndef TFALL_GAME_H
#define TFALL_GAME_H
#include <Node/SceneManager.h>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Game {

public:
    void HandleEvents();
    void Update(sf::Time dt);
    void Render();

private:

};


#endif //TFALL_GAME_H
