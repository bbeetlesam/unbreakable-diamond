#ifndef CONST
#define CONST

#include <SFML/Graphics.hpp>
using str = std::string;

/// Constant variables
namespace cn{
    // Window's name
    constexpr const char* WindowName = "Unbreakable Diamond";

    // Window's initial size
    constexpr sf::Vector2u InitWindowSize = {1440*5/6, 1080*5/6};

    // Desktop's size
    const sf::VideoMode DesktopSize = sf::VideoMode::getDesktopMode();

    // Maximum FPS
    constexpr int MaxFPS = 60;

    // Background color
    constexpr sf::Color BgColor = sf::Color(33, 36, 56);
}

#endif // CONST