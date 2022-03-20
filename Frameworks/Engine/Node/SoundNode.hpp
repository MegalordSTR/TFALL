//
// Created by Admin on 16.03.2022.
//

#ifndef TEST_SOUNDNODE_H
#define TEST_SOUNDNODE_H

#include "SceneNode.hpp"
#include <Engine/Resources/SoundPlayer.hpp>

namespace Engine
{
    class SoundNode : public SceneNode
    {
    public:
        explicit SoundNode(SoundPlayer& player);

        void playSound(Resources::SoundEffect sound);

    private:
        SoundPlayer& player;
    };
}



#endif //TEST_SOUNDNODE_H
