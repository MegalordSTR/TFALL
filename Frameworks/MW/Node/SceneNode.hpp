//
// Created by Admin on 16.03.2022.
//

#ifndef TEST_SCENENODE_H
#define TEST_SCENENODE_H

#include <MW/Command/CommandQueue.hpp>
#include "CategoryIdentifiers.hpp"

#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>

namespace MW
{
class SceneNode : public sf::Drawable, public sf::Transformable, private sf::NonCopyable, private std::enable_shared_from_this<SceneNode>
    {
    public:
        explicit SceneNode();

        void attachChild(std::shared_ptr<SceneNode> ptr);
        std::shared_ptr<SceneNode> detachChild(const SceneNode& node);

        void update(sf::Time dt, CommandQueue& commands);
        void onCommand(const Command& command, sf::Time dt);

        virtual bool isMarkedForRemoval() const;
        void removeMarked();

        void setNodeCategory(CategoryType type);

    protected:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const; // To override
        void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

        virtual void updateCurrent(sf::Time dt, CommandQueue& commands); // To override
        void updateChildren(sf::Time dt, CommandQueue& commands);

    private:
        std::weak_ptr<SceneNode> parent;
        std::vector<std::shared_ptr<SceneNode>> children;
        CategoryType nodeType;
    };
}

#endif //TEST_SCENENODE_H
