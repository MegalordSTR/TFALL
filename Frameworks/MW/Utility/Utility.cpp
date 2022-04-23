#include "Utility.h"

#include <cassert>
#include <chrono>
#include <random>

namespace
{
    std::default_random_engine createRandomEngine()
    {
        auto seed = static_cast<unsigned long>(std::time(nullptr));
        return std::default_random_engine(seed);
    }

    auto RandomEngine = createRandomEngine();
}

// Return [0, exclusiveMax)
int randIntN(int exclusiveMax)
{
    std::uniform_int_distribution<int> distr(0, exclusiveMax - 1);
    return distr(RandomEngine);
}

// Return [0, exclusiveMax)
float randFloatN(float exclusiveMax)
{
    std::uniform_real_distribution<float> distr(0, exclusiveMax);
    return distr(RandomEngine);
}

// Return [0, 1)
inline float randFloatNorm()
{
    return randFloatN(1);
}


float length(sf::Vector2f vector)
{
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

sf::Vector2f unitVector(sf::Vector2f vector)
{
    assert(vector != sf::Vector2f(0.f, 0.f));
    return vector / length(vector);
}

sf::Vector2f divideVector(const sf::Vector2f &vector, float div) {
    return {vector.x / div, vector.y / div};
}


