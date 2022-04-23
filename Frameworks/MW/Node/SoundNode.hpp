#pragma once

#include "SceneNode.hpp"
#include <MW/Resources/SoundPlayer.hpp>

namespace MW
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
