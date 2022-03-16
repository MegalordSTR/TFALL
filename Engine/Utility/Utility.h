//
// Created by Admin on 16.03.2022.
//

#ifndef TEST_UTILITY_H
#define TEST_UTILITY_H

#include <SFML/Graphics.hpp>

// Random number generation
int	randIntN(int exclusiveMax);
float randFloatN(float exclusiveMax);

// Returns float [0;1]
float randFloatNorm();


// Vector operations
float			length(sf::Vector2f vector);
sf::Vector2f	unitVector(sf::Vector2f vector);

#endif //TEST_UTILITY_H