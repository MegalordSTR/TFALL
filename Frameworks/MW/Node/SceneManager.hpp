#pragma once

#include <MW/Node/SceneNode.hpp>

#include <SFML/System/NonCopyable.hpp>

#include <unordered_map>
#include <memory>


namespace MW
{
    enum class Layer : int
    {
        Background = 0,
        Sound = 1,
        Front = 2
    };


    class SceneManager : private sf::NonCopyable
    {
    public:
        explicit SceneManager();
        ~SceneManager();

        void addLayer(Layer layer);
        SceneNode& getLayer(Layer layer);

    private:
        std::unordered_map<Layer, std::shared_ptr<SceneNode>> layers;
    };
}
