//
// Created by Admin on 16.03.2022.
//

#include "SceneNode.hpp"

#include <cassert>
#include <memory>

namespace Engine
{
    SceneNode::SceneNode() :
            parent(),
            children(),
            nodeType(CategoryType::None)
    {
    }

    void SceneNode::attachChild(std::shared_ptr<SceneNode> ptr)
    {
        ptr->parent = weak_from_this();
        children.push_back(ptr);
    }

    std::shared_ptr<SceneNode> SceneNode::detachChild(const SceneNode& node)
    {
        auto found = std::find_if(
                children.begin(),
                children.end(),
                [&](const std::shared_ptr<SceneNode>& child)
                {
                    return child.get() == &node;
                }
        );

        assert(found != children.end());

        std::shared_ptr<SceneNode> result = *found;
        result->parent.reset();

        children.erase(found);

        return result;
    }

    void SceneNode::update(sf::Time dt, CommandQueue& commands)
    {
        updateCurrent(dt, commands);
        updateChildren(dt, commands);
    }

    void SceneNode::onCommand(const Command& command, sf::Time dt)
    {
        if (static_cast<unsigned int>(nodeType) & static_cast<unsigned int>(command.category))
        {
            command.action(*this, dt);
        }

        for (auto& node : children)
        {
            node->onCommand(command, dt);
        }
    }

    bool SceneNode::isMarkedForRemoval() const
    {
        return false;
    }

    void SceneNode::removeMarked()
    {
        auto toRemove = std::remove_if(children.begin(), children.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));
        children.erase(toRemove, children.end());

        for (auto& child : children)
        {
            child->removeMarked();
        }
    }

    void SceneNode::setNodeCategory(CategoryType type)
    {
        nodeType = type;
    }

    void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        drawCurrent(target, states);
        drawChildren(target, states);
    }


    void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // To override
    }

    void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (auto& node : children)
        {
            node->draw(target, states);
        }
    }

    void SceneNode::updateCurrent(sf::Time dt, CommandQueue& commands)
    {
        // To override
    }

    void SceneNode::updateChildren(sf::Time dt, CommandQueue& commands)
    {
        for (auto& node : children)
        {
            node->update(dt, commands);
        }
    }
}