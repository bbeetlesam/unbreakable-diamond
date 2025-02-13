#ifndef GAME
#define GAME

#define PI 3.14159265358979323846 // taken from math.h macro M_PI

#include "const.hpp"
#include "resources.hpp"
#include "func.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <memory> // smart pointers unique_ptr

// Class for Shield arc
class ArcShield{
    public:
        ArcShield(float radius, float arcAngle, float thickness, sf::Vector2f center, unsigned int health);

        void init(float radius, float arcAngle, float thickness, sf::Vector2f center);
        void update(sf::Vector2f mousePos);
        void draw(sf::RenderWindow& window);

        // Get current angle of the shield in degrees
        float getAngle() const { return currentAngle; }

    private:
        float radius;
        float arcAngle;
        float thickness;
        sf::Vector2f center;
        unsigned int health;

        float currentTheta; // in radians
        float currentAngle; // in degrees
        const int arcSegments = 20;
        sf::VertexArray arc;
    
        void generateArc(float rotationAngle = 0.0f);
};

// Class for Hand object
class Hand{
    public:
        Hand(const sf::Vector2f& startPos, const sf::Vector2f& targetPos);
        ~Hand();

    private:
        sf::Vector2f startPos;
        sf::Vector2f targetPos;
        unsigned int damage;
};

//
class HardHand : public Hand{
    public:
        HardHand(const sf::Vector2f& startPos, const sf::Vector2f& targetPos);
        ~HardHand();

    private:
        unsigned int damage;
};

// Class for Game's logic manager
class Game{
    public:
        Game();
        ~Game();

        // Main function to run the game
        void run();

    private:
        sf::RenderWindow window;
        sf::Vector2u windowSize;
        sf::Image icon;
        sf::View view;
        bool isFullscreen;
        bool isRunning;

        std::vector<sf::CircleShape> circles;
        std::vector<std::unique_ptr<Hand>> hands;
        std::vector<sf::Sprite> sprites;

        sf::Vector2f lastMousePos;

        std::unique_ptr<ArcShield> shield;

        ResourceManager resources;
        ObjectManager assets{resources};

        // Function to handle events (mouse, input, etc)
        void handleEvents();
        // Function to update the game's logic
        void update();
        // Function to render the game's drawable objects
        void render();
        // Function used to initialize data
        void initData();
        // Function to load resources
        void initResources();

        // Function used to toggle fullscreen mode
        void toggleFullscreen(sf::RenderWindow& window);
};

#endif // GAME