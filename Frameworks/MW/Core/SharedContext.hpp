#pragma once

#include <MW/Resources/ResourceIdentifiers.hpp>
#include <MW/Resources/SoundPlayer.hpp>
#include "InputManager.hpp"
#include "SFML/Graphics.hpp"

namespace MW
{
    struct SharedContext {
        InputManager* inputManager;
        sf::RenderWindow* window;
        FontHolder* fonts;
        TextureHolder* textures;
        SoundPlayer* soundPlayer;
    };
}
