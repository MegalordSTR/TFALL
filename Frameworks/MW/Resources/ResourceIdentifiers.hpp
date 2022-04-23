#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace MW
{
	namespace Resources
	{
		enum class Font
		{
			Main
		};

		enum class Texture
		{
            Block
		};

		enum class SoundEffect
		{
            Background
		};
	}

    template <typename Resource, typename Identifier>
    class ResourceHolder;

    typedef ResourceHolder<sf::Font, Resources::Font> FontHolder;
    typedef ResourceHolder<sf::Texture, Resources::Texture> TextureHolder;
    typedef ResourceHolder<sf::SoundBuffer, Resources::SoundEffect> SoundBufferHolder;

}