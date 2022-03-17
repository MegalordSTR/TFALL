//
// Created by Admin on 16.03.2022.
//

#include "SceneManager.h"
#include <cassert>

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::addLayer(Engine::Layer layer)
{
    layers.try_emplace(layer, std::make_shared<SceneNode>());
}

SceneNode& SceneManager::getLayer(Engine::Layer layer)
{
    auto found = layers.find(layer);
    assert(found != layers.end());

    return *found->second;
}