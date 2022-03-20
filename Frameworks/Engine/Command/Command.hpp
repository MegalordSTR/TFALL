//
// Created by Admin on 16.03.2022.
//

#ifndef TEST_COMMAND_H
#define TEST_COMMAND_H


#include <Engine/Node/CategoryIdentifiers.hpp>

#include <SFML/Graphics.hpp>
#include <functional>
#include <cassert>

namespace Engine
{
    class SceneNode;

    struct Command
    {
        typedef std::function<void(SceneNode&, sf::Time)> Action;

        Command(Action fn, CategoryType category);
        Action action;
        CategoryType category;
    };

    template<typename GameObject, typename Function>
    Command::Action derrivedAction(Function fn)
    {
        return [=](SceneNode& node, sf::Time dt)
        {
            assert(dynamic_cast<GameObject*>(&node) != nullptr);

            fn(static_cast<GameObject&>(node), dt);
        };
    }
}



#endif //TEST_COMMAND_H
