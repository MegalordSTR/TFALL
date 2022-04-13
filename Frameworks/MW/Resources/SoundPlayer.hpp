//
// Created by Admin on 16.03.2022.
//

#ifndef TEST_SOUNDPLAYER_H
#define TEST_SOUNDPLAYER_H

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Audio.hpp>

#include <list>

namespace MW {

    class SoundPlayer : private sf::NonCopyable {
    public:
        SoundPlayer();

        void play(Resources::SoundEffect id);

        void removeStoppedSounds();

        void stopAndRemoveAll();

    private:
        SoundBufferHolder soundBuffers;

        std::list<sf::Sound> playingSounds;
    };
}

#endif //TEST_SOUNDPLAYER_H
