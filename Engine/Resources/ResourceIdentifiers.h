#ifndef TEST_RESOURCEIDENTIFIERS_H
#define TEST_RESOURCEIDENTIFIERS_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace Game
{
	namespace Resources
	{
		enum class Font
		{
			Main
		};

		const int BubbleTexturesCount = 8;

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

typedef ResourceHolder<sf::Font, Game::Resources::Font> FontHolder;
typedef ResourceHolder<sf::Texture, Game::Resources::Texture> TextureHolder;
typedef ResourceHolder<sf::SoundBuffer, Game::Resources::SoundEffect> SoundBufferHolder;

#endif