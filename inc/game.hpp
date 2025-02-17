#ifndef GAME
#define GAME

#include "const.hpp"
#include "resources.hpp"
#include "func.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <unordered_map>
#include <optional>
#include <map>
#include <cmath>
#include <memory> // smart pointers unique_ptr
#include <deque>
#include <algorithm>

#define PI 3.14159265358979323846 // taken from math.h macro M_PI

// Base class for Hand objects
class Hand{
    public:
        virtual void update(float deltaTime) = 0;
        virtual void draw(sf::RenderWindow& window);
    
        sf::Vector2f getPosition() const { return position; }

    protected:
        // Hand constructor
        Hand(sf::Vector2f startPos, const sf::Texture& armTex, const sf::Texture& handTex);

        sf::Vector2f getDirection() const { return direction; }
        sf::Vector2f getTargetPos() const { return spawnPos; }
        float getSpeed() const { return speed; }

        void setPosition(sf::Vector2f newPos) { position = newPos; }

        sf::Vector2f spawnPos;

        unsigned int damage;
        unsigned int health;

        sf::Vector2f position;
        sf::Vector2f direction;
        float rotation;
        float scale;
        float speed;

        float segmentSpacing = 60.0f;
        int maxSegments = 20;
        std::deque<sf::Vector2f> previousPositions; // Posisi lama untuk lengan

        sf::Texture armTexture;
        sf::Texture handTexture;
        sf::Sprite handSprite;
        std::vector<sf::Sprite> arms;

    private:
        sf::Vector2f targetPos{0.f, 0.f};
};

// Class for Shield arc
class ArcShield{
    public:
        ArcShield(float radius, float arcAngle, float thickness, sf::Vector2f center, unsigned int health);

        void init(float radius, float arcAngle, float thickness, sf::Vector2f center);
        void update(sf::Vector2f mousePos);
        void draw(sf::RenderWindow& window);

        // Get current angle of the shield in degrees
        float getAngle() const { return currentAngle; }

        bool isHandInside(const Hand& hand, float offset = 0.f) const;
        bool isHandBlocked(const Hand& hand) const;

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

// Class for Game's logic manager
class Game{
    public:
        Game();
        ~Game();

        // Main function to run the game
        void run();

    private:
        ResourceManager resources;
        ObjectManager assets{resources};

        sf::RenderWindow window;
        sf::Vector2u windowSize;
        sf::Image icon;
        sf::View view;
        bool isFullscreen;
        bool isRunning;

        std::vector<sf::CircleShape> circles;
        std::vector<std::unique_ptr<Hand>> hands;

        sf::Vector2f lastMousePos;
        sf::Clock clock;
        float deltaTime;

        std::unique_ptr<ArcShield> shield;

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