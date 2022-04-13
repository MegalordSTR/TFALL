//
// Created by Admin on 16.03.2022.
//

#include "SoundPlayer.hpp"

namespace MW {

    SoundPlayer::SoundPlayer() :
            soundBuffers(),
            playingSounds() {

        soundBuffers.load(Resources::SoundEffect::Background, "Polka_Loop.ogg");
    }

    void SoundPlayer::play(Resources::SoundEffect id) {
        const sf::SoundBuffer &buffer = soundBuffers.get(id);

        playingSounds.emplace_back(sf::Sound(buffer));
        sf::Sound &sound = playingSounds.back();
        sound.setVolume(5.f);
        sound.play();
    }

    void SoundPlayer::removeStoppedSounds() {
        playingSounds.remove_if([](const sf::Sound &sound) {
            return static_cast<int>(sound.getStatus()) == static_cast<int>(sf::Sound::Stopped);
        });
    }

    void SoundPlayer::stopAndRemoveAll() {
        playingSounds.erase(playingSounds.begin(), playingSounds.end());
    }
}
