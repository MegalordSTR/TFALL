//
// Created by Admin on 16.03.2022.
//

#include "SceneNode.h"

#include <cassert>
#include <memory>

SceneNode::SceneNode() :
        parent(nullptr),
        children(),
        nodeType(Engine::CategoryType::None)
{
}

void SceneNode::attachChild(std::unique_ptr<SceneNode> ptr)
{
    ptr.get()->parent = this;
    children.push_back(std::move(ptr));
}

std::unique_ptr<SceneNode> SceneNode::detachChild(const SceneNode& ptr)
{
    auto found = std::find_if(children.begin(), children.end(), [&](std::unique_ptr<SceneNode>& node)
                              { return node.get() == &ptr; }
    );

    assert(found != children.end());

    std::unique_ptr<SceneNode> result = std::move(*found);
    result->parent = nullptr;

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

void SceneNode::setNodeCategory(Engine::CategoryType type)
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
