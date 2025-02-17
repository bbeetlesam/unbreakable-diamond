#ifndef HAND
#define HAND

#include "game.hpp"

// Class for Normal Hand
class NormalHand : public Hand{
    public:
        NormalHand(sf::Vector2f startPos, const sf::Texture& armTex, const sf::Texture& handTex);
        void update(float deltaTime) override;
    
    private:
        const float handSpeed = 350.0f;
};

// Class for Fast Hand
class FastHand : public Hand {
    public:
        FastHand(sf::Vector2f startPos, const sf::Texture& armTex, const sf::Texture& handTex);
        void update(float deltaTime) override;

    private:
        const float handSpeed = 450.0f;
};

#endif // HAND