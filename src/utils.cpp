#include "func.hpp"

void drawCrossLine(sf::RenderWindow& window, sf::Color vertColor, sf::Color horiColor){
    // Dapatkan view yang sedang aktif
    sf::View currentView = window.getView();

    // Dapatkan ukuran view dalam world coordinates
    sf::Vector2f viewSize = currentView.getSize();
    sf::Vector2f viewCenter = currentView.getCenter();

    sf::Vertex crossline[] = {
        // Vertical line (garis vertikal di tengah)
        {{viewCenter.x, viewCenter.y - viewSize.y / 2}, vertColor}, 
        {{viewCenter.x, viewCenter.y + viewSize.y / 2}, vertColor},

        // Horizontal line (garis horizontal di tengah)
        {{viewCenter.x - viewSize.x / 2, viewCenter.y}, horiColor}, 
        {{viewCenter.x + viewSize.x / 2, viewCenter.y}, horiColor}
    };

    window.draw(crossline, std::size(crossline), sf::PrimitiveType::Lines);
}

sf::Vector2f getRandomSpawnPoint(const sf::Vector2f& center, float radiusX, float radiusY, std::mt19937& rng){
    std::uniform_real_distribution<float> angleDist(0.0f, 2 * PI); // Sudut acak 0 - 2*PI
    float angle = angleDist(rng);

    // Penyesuaian jarak berdasarkan sumbu elips
    float adjustedX = radiusX * cos(angle);
    float adjustedY = radiusY * sin(angle);

    return sf::Vector2f(center.x + adjustedX, center.y + adjustedY);
}

sf::Vector2f normalize(const sf::Vector2f& vec) {
    float length = std::sqrt(vec.x * vec.x + vec.y * vec.y);
    return length != 0 ? vec / length : sf::Vector2f(0, 0);
}