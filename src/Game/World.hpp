//
// Created by Admin on 18.03.2022.
//

#ifndef TFALL_WORLD_HPP
#define TFALL_WORLD_HPP

#include "GridSpriteNode.hpp"
#include "TetrisGrid.hpp"

#include <MW/Command/CommandQueue.hpp>
#include <MW/Node/SceneManager.hpp>
#include <MW/Node/SoundNode.hpp>
#include <MW/Node/Label.hpp>
#include <MW/Input/InputManager.hpp>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <memory>
#include <utility>

class World {
public:
    World(sf::RenderWindow &window, MW::SoundPlayer &soundPlayer, MW::TextureHolder &textureHolder, MW::FontHolder &fontsHolder, MW::InputManager &inputManager);

    ~World();

    void update(sf::Time dt);
    void draw();

    bool CheckSpace();
    int32_t GetScore();

    MW::CommandQueue& getCommandQueue();

private:
    void moveFigureLeft(MW::EventDetails* details);
    void moveFigureRight(MW::EventDetails* details);
    void rotateFigure(MW::EventDetails* details);

private:
    sf::RenderWindow& window;
    MW::SoundPlayer& soundPlayer;
    MW::TextureHolder& textureHolder;
    MW::InputManager& inputManager;

    MW::CommandQueue commandQueue;
    MW::SceneManager sceneManager;

    sf::View worldView;
    float gridMargin;

    int nextFigureColorNum;
    int figureColorsNum;

    std::shared_ptr<TetrisGrid> tetrisGrid;
};


#endif //TFALL_WORLD_HPP
