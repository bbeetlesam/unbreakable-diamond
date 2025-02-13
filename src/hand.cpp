#include "game.hpp"

// Hand constructor
Hand::Hand(const sf::Vector2f& startPos, const sf::Vector2f& targetPos)
    : startPos(startPos), targetPos(targetPos), damage(10u)
{
    
}

// Hand destructor
Hand::~Hand(){

}

//