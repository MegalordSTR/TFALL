//
// Created by Admin on 18.03.2022.
//

#ifndef TFALL_WORLD_HPP
#define TFALL_WORLD_HPP

#include "GridSpriteNode.hpp"
#include "Block.hpp"
#include "Figure.hpp"
#include "TetrisGrid.hpp"

#include <MW/Command/CommandQueue.hpp>
#include <MW/Node/SceneManager.hpp>
#include <MW/Node/SoundNode.hpp>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <memory>
#include <utility>

class World {
public:
    World(sf::RenderWindow& window, MW::SoundPlayer& soundPlayer, MW::TextureHolder& textureHolder);

    ~World();

    void update(sf::Time dt);
    void draw();

    MW::CommandQueue& getCommandQueue();

private:

    bool isFigureLanded();
    void transferNonStaticFigure();
    void shrinkFullLines();
    void spawnFigure(int blockColor);

private:
    MW::TextureHolder& textureHolder;

    MW::CommandQueue commandQueue;
    MW::SceneManager sceneManager;
    MW::SoundPlayer& soundPlayer;

    sf::RenderWindow& window;
    sf::View worldView;

    float gridMargin;

    std::weak_ptr<Figure> fallingFigure;
    std::weak_ptr<Figure> staticFigure;

    int nextFigureColorNum;
    int figureColorsNum;

    std::shared_ptr<TetrisGrid> tetrisGrid;
};


#endif //TFALL_WORLD_HPP
