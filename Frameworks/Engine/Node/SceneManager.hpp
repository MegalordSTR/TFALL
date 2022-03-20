//
// Created by Admin on 16.03.2022.
//

#ifndef TEST_SCENEMANAGER_H
#define TEST_SCENEMANAGER_H

#include <Engine/Node/SceneNode.hpp>

#include <SFML/System/NonCopyable.hpp>

#include <unordered_map>
#include <memory>


namespace Engine
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


#endif //TEST_SCENEMANAGER_H
