#ifndef FUNC
#define FUNC

#define PI 3.14159265358979323846
#include "const.hpp"
#include <random>

/// static_cast to primitive data types
template <typename T>
constexpr T to(T value){
    return static_cast<T>(value);
}

/// @brief draw crosslines (made for debugging) @param window @param verticalColor def: red @param horizontalColor def: blue
void drawCrossLine(sf::RenderWindow& window, sf::Color vertColor = sf::Color::White, sf::Color horiColor = sf::Color::White);

/// @brief get random spawn point on a fixed distance pattern (for hand) @param center @param radiusX @param radiusY @param rng @return coordinates
sf::Vector2f getRandomSpawnPoint(const sf::Vector2f& center, float radiusX, float radiusY, std::mt19937& rng);

/// Normalize a vector @param vec @return normalized vector
sf::Vector2f normalize(const sf::Vector2f& vec);

#endif // FUNC