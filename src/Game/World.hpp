//
// Created by Admin on 18.03.2022.
//

#ifndef TFALL_WORLD_HPP
#define TFALL_WORLD_HPP

#include "Grid.hpp"

#include <Engine/Command/CommandQueue.hpp>
#include <Engine/Node/SceneManager.hpp>
#include <Engine/Node/SoundNode.hpp>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <memory>

class World {
public:
    World(sf::RenderWindow& window, Engine::SoundPlayer& soundPlayer, Engine::TextureHolder& textureHolder);

    ~World();

    void update(sf::Time dt);
    void draw();

private:
    Engine::CommandQueue commandQueue;
    Engine::SceneManager sceneManager;

    sf::RectangleShape backgroundBig;
    sf::RectangleShape backgroundMap;
    Engine::SoundPlayer& soundPlayer;

    sf::RenderWindow& window;
    sf::View worldView;

    std::weak_ptr<Grid> grid;
    int gridMargin;
};


#endif //TFALL_WORLD_HPP
