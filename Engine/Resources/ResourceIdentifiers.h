#ifndef TEST_RESOURCEIDENTIFIERS_H
#define TEST_RESOURCEIDENTIFIERS_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>



namespace Engine
{
	namespace Resources
	{
		enum class Font
		{
			Main
		};

		enum class Texture
		{

		};

		enum class SoundEffect
		{

		};
	}

    template <typename Resource, typename Identifier>
    class ResourceHolder;

    typedef ResourceHolder<sf::Font, Resources::Font> FontHolder;
    typedef ResourceHolder<sf::Texture, Resources::Texture> TextureHolder;
    typedef ResourceHolder<sf::SoundBuffer, Resources::SoundEffect> SoundBufferHolder;

}
#endif