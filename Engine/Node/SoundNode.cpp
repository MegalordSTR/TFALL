//
// Created by Admin on 16.03.2022.
//

#include "SoundNode.h"

SoundNode::SoundNode(SoundPlayer& player) :
        player(player)
{
    setNodeCategory(Engine::CategoryType::SoundEffect);
}

void SoundNode::playSound(Engine::Resources::SoundEffect sound)
{
    player.play(sound);
}
