#pragma once

#include <SFML/Graphics.hpp>

// Random number generation
int	randIntN(int exclusiveMax);
float randFloatN(float exclusiveMax);

// Returns float [0;1]
float randFloatNorm();


// Vector operations
float			length(sf::Vector2f vector);
sf::Vector2f	unitVector(sf::Vector2f vector);
sf::Vector2f	divideVector(const sf::Vector2f& vector, float div);

template<typename T>
sf::Vector2f vectorScaleRatio(const sf::Vector2<T>& vectorL, const sf::Vector2<T>& vectorR) {
    return sf::Vector2f(static_cast<float>(vectorL.x) / static_cast<float>(vectorR.x), static_cast<float>(vectorL.y) / static_cast<float>(vectorR.y));
}