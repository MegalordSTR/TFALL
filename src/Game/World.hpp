//
// Created by Admin on 18.03.2022.
//

#ifndef TFALL_WORLD_HPP
#define TFALL_WORLD_HPP

#include "Grid.hpp"

#include <MW/Command/CommandQueue.hpp>
#include <MW/Node/SceneManager.hpp>
#include <MW/Node/SoundNode.hpp>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <memory>

class World {
public:
    World(sf::RenderWindow& window, MW::SoundPlayer& soundPlayer, MW::TextureHolder& textureHolder);

    ~World();

    void update(sf::Time dt);
    void draw();

    MW::CommandQueue& getCommandQueue();

private:
    MW::CommandQueue commandQueue;
    MW::SceneManager sceneManager;

    sf::RectangleShape infoPanel;
    sf::RectangleShape mapPanel;
    MW::SoundPlayer& soundPlayer;

    sf::RenderWindow& window;
    sf::View worldView;

    std::weak_ptr<Grid> grid;
    float gridMargin;
};


#endif //TFALL_WORLD_HPP
