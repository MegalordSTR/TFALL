#include "SceneManager.hpp"
#include <cassert>

namespace MW {
    SceneManager::SceneManager()
    {
    }

    SceneManager::~SceneManager()
    {
    }

    void SceneManager::addLayer(Layer layer)
    {
        layers.try_emplace(layer, std::make_shared<SceneNode>());
    }

    SceneNode& SceneManager::getLayer(Layer layer)
    {
        auto found = layers.find(layer);
        assert(found != layers.end());

        return *found->second;
    }
}
