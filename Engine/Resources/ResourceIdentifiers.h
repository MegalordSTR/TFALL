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
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Font, Engine::Resources::Font> FontHolder;
typedef ResourceHolder<sf::Texture, Engine::Resources::Texture> TextureHolder;
typedef ResourceHolder<sf::SoundBuffer, Engine::Resources::SoundEffect> SoundBufferHolder;

#endif