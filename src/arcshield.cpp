#include "game.hpp"
#include "easings.hpp"

ArcShield::ArcShield(float radius, float arcAngle, float thickness, sf::Vector2f center, unsigned int health)
    : radius(radius), arcAngle(arcAngle), thickness(thickness), center(center), health(health), currentTheta(0.f), arc(sf::PrimitiveType::Triangles)
{
    generateArc(currentTheta);
}

void ArcShield::generateArc(float rotationAngle){
    arc.clear();
    for (int i = 0; i < arcSegments; ++i) {
        float angle1 = rotationAngle + (arcAngle / 2.f - i * (arcAngle / arcSegments)) * (PI / 180.f);
        float angle2 = rotationAngle + (arcAngle / 2.f - (i + 1) * (arcAngle / arcSegments)) * (PI / 180.f);
        
        sf::Vector2f p1 = center + sf::Vector2f{radius * std::cos(angle1), radius * std::sin(angle1)};
        sf::Vector2f p2 = center + sf::Vector2f{radius * std::cos(angle2), radius * std::sin(angle2)};
        sf::Vector2f p3 = center + sf::Vector2f{(radius - thickness) * std::cos(angle1), (radius - thickness) * std::sin(angle1)};
        sf::Vector2f p4 = center + sf::Vector2f{(radius - thickness) * std::cos(angle2), (radius - thickness) * std::sin(angle2)};
        
        sf::Color arcColor{sf::Color::Cyan};
        
        arc.append(sf::Vertex{p1, arcColor});
        arc.append(sf::Vertex{p2, arcColor});
        arc.append(sf::Vertex{p3, arcColor});
        
        arc.append(sf::Vertex{p3, arcColor});
        arc.append(sf::Vertex{p2, arcColor});
        arc.append(sf::Vertex{p4, arcColor});
    }
}

void ArcShield::init(float radius, float arcAngle, float thickness, sf::Vector2f center){
    this->radius = radius;
    this->arcAngle = arcAngle;
    this->thickness = thickness;
    this->center = center;
    generateArc(currentTheta);
}

void ArcShield::update(sf::Vector2f mousePos){
    float dx = mousePos.x - center.x;
    float dy = mousePos.y - center.y;

    // Count the target angle (radian)
    float targetTheta = std::atan2(dy, dx);

    // Easing speed (0.0 - 1.0)
    float alpha = 0.4f;

    // Ensure rotation follows the shortest path (to avoid Shortest Path Rotation Problem)
    float deltaTheta = targetTheta - currentTheta;

    // Normalize deltaTheta in range -π to π
    while (deltaTheta > PI) deltaTheta -= 2 * PI;
    while (deltaTheta < -PI) deltaTheta += 2 * PI;

    // Ease Out easing (this is 'the' technique)
    currentTheta += ease::linear(alpha) * deltaTheta;

    // Convert radian to degree
    currentAngle = currentTheta * 180 / PI;

    generateArc(currentTheta);
}

void ArcShield::draw(sf::RenderWindow& window){
    window.draw(arc);
}
