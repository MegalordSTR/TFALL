//
// Created by Admin on 16.03.2022.
//

#ifndef TEST_SOUNDNODE_H
#define TEST_SOUNDNODE_H

#include "SceneNode.h"
#include <Resources/SoundPlayer.h>

class SoundNode : public SceneNode
{
public:
    explicit SoundNode(SoundPlayer& player);

    void playSound(Engine::Resources::SoundEffect sound);

private:
    SoundPlayer& player;
};


#endif //TEST_SOUNDNODE_H
