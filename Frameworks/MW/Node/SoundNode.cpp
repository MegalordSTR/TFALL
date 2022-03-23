//
// Created by Admin on 16.03.2022.
//

#include "SoundNode.hpp"
namespace MW
{
    SoundNode::SoundNode(SoundPlayer& player) :
            player(player)
    {
        setNodeCategory(CategoryType::TypeSoundEffect);
    }

    void SoundNode::playSound(Resources::SoundEffect sound)
    {
        player.play(sound);
    }
}
